/****************************************Copyright (c)************************************************                                 
**--------------File Info-----------------------------------------------------------------------------
** File name:			     main.c
** Last modified Date:          
** Last Version:		   
** Descriptions:		   ʹ�õ�SDK�汾-SDK_15.2
**						
**----------------------------------------------------------------------------------------------------
** Created by:			
** Created date:		2019-1-16
** Version:			    1.0
** Descriptions:		2.4G����ͨѶ����ʵ��
**--------------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#include "app_uart.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
//ESB��Ҫ���õ�ͷ�ļ�
#include "nrf_esb.h"
#include "nrf_error.h"
#include "nrf_esb_error_codes.h"
#include "sdk_common.h"

/* ������Ҫ�õ�IK-52832DK�������е�ָʾ��D1��UART��ռ�õ�nRF52832������Դ����
P0.17�����������ָʾ��D1


P0.06�����������TXD
P0.08�����룺����RXD

��Ҫ������ñ�̽�P0.17 P0.06 P0.08
*/

#define UART_TX_BUF_SIZE 256       //���ڷ��ͻ����С���ֽ�����
#define UART_RX_BUF_SIZE 256       //���ڽ��ջ����С���ֽ�����

//static nrf_esb_payload_t        tx_payload;

static nrf_esb_payload_t        rx_payload;

//�����¼��ص��������ú������ж��¼����Ͳ����д���
void uart_error_handle(app_uart_evt_t * p_event)
{
    //ͨѶ�����¼�
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    //FIFO�����¼�
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}
//���ڳ�ʼ�����ã�������115200bps���ر�Ӳ������
void uart_config(void)
{
  uint32_t err_code;
	
	//���崮��ͨѶ�������ýṹ�岢��ʼ��
  const app_uart_comm_params_t comm_params =
  {
    RX_PIN_NUMBER,//����uart��������
    TX_PIN_NUMBER,//����uart��������
    RTS_PIN_NUMBER,//����uart RTS���ţ�ע�����عرպ���Ȼ������RTS��CTS���ţ����ǲ�������
    CTS_PIN_NUMBER,//����uart CTS����
    APP_UART_FLOW_CONTROL_DISABLED,//�ر�uartӲ������
    false,//��ֹ��ż����
    NRF_UART_BAUDRATE_115200//uart����������Ϊ115200bps
  };
  //��ʼ�����ڣ�ע�ᴮ���¼��ص�����
  APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

  APP_ERROR_CHECK(err_code);		
}
//ESB�¼��ص�����
void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    uint8_t i;
	  //�ж��¼�����
	  switch (p_event->evt_id)
    {
        //���ͳɹ��¼�
			  case NRF_ESB_EVENT_TX_SUCCESS:
            printf("TX SUCCESS EVENT");
            break;
				//����ʧ���¼�
        case NRF_ESB_EVENT_TX_FAILED:
            printf("TX FAILED EVENT");
            (void) nrf_esb_flush_tx();
            (void) nrf_esb_start_tx();
            break;
				//�����¼�
        case NRF_ESB_EVENT_RX_RECEIVED:
            //��ȡ���յ����ݺ͸����ݰ���RSSI
				    if (nrf_esb_read_rx_payload(&rx_payload) == NRF_SUCCESS)
            {
                //���ڴ�ӡ�����յ����ݳ���
							  printf("length = %02X  ",(uint8_t)rx_payload.length); 
							  //���ڴ�ӡ�����յ�����
							  printf("DATA = ");
							  for(i=0;i<rx_payload.length;i++)printf(" %02X",(uint8_t)rx_payload.data[i]);  
							  //���ڴ�ӡ���ð����ݵ�RSSI
							  printf("  RSSI = -%d",(uint8_t)rx_payload.rssi);    
							  printf("\r\n");
                nrf_gpio_pin_toggle(LED_1);                 //D1ָʾ��״̬��ת��ָʾ�ƽ��յ��µ�����      
            }
            break;
    }
}
//��ʼ����Ƶʱ�ӣ�2.4G����ʹ�ø�Ƶʱ�ӣ����ұ���ʹ���ⲿ��32MHz������Ϊʱ��Դ�������޷���֤�źŵľ���
void clocks_start( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}
//��ʼ��ESB
uint32_t esb_init( void )
{
    uint32_t err_code;
    uint8_t base_addr_0[4] = {0xE4, 0xE3, 0xE2, 0xE1};
    uint8_t base_addr_1[4] = {0xC2, 0xC2, 0xC2, 0xC2};
    uint8_t addr_prefix[8] = {0xE5, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };
    //����ESB���ýṹ�壬��ʹ��Ԥ�ȶ����Ĭ�ϲ�����ESB���ýṹ�帳ֵ��֮�������Ҫ�޸�
    nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;
		
		//2.4GЭ�飺ESB����̬���ݳ���
    nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
		//ESB�ط��ӳ�ʱ�䣺600us
    nrf_esb_config.retransmit_delay         = 600;
		//ESB�������ʣ�2M
    nrf_esb_config.bitrate                  = NRF_ESB_BITRATE_2MBPS;
		//ESB�¼��ص�����
    nrf_esb_config.event_handler            = nrf_esb_event_handler;
    //ESBģʽ��PRX�������գ�
		nrf_esb_config.mode                     = NRF_ESB_MODE_PRX;
    //�ر��Զ�Ӧ��
		nrf_esb_config.selective_auto_ack       = true;

    //��ʼ��ESB
    err_code = nrf_esb_init(&nrf_esb_config);
    //��鷵�صĴ������
    VERIFY_SUCCESS(err_code);
    //���õ�ַ0
    err_code = nrf_esb_set_base_address_0(base_addr_0);
    VERIFY_SUCCESS(err_code);
    //���õ�ַ1
    err_code = nrf_esb_set_base_address_1(base_addr_1);
    VERIFY_SUCCESS(err_code);
    //���õ�ַǰ׺
    err_code = nrf_esb_set_prefixes(addr_prefix, NRF_ESB_PIPE_COUNT);
    VERIFY_SUCCESS(err_code);
		
		//�����ŵ���ע�⣺����˺ͽ��ն�ֻ�д���ͬһ���ŵ����ܴ�������
		//Ƶ�� = (2400 + channel) MHz��channelΪ���������鷶Χ  0<channel<83
		err_code = nrf_esb_set_rf_channel(50);

    return err_code;
}
/***************************************************************************
* ��  �� : main���� 
* ��  �� : �� 
* ����ֵ : int ����
**************************************************************************/
int main(void)
{
		uint32_t err_code;
		//��ʼ���������ϵ�4��LED����������LED��GPIO����Ϊ�����
		bsp_board_init(BSP_INIT_LEDS);
		//��ʼ������
		uart_config();

		clocks_start();

		err_code = esb_init();
		APP_ERROR_CHECK(err_code);
		err_code = nrf_esb_start_rx(); //����ESB����

		while(true)
		{
 	
		
  }
}
/********************************************END FILE**************************************/
