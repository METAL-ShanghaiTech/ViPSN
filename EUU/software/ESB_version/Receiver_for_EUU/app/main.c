/****************************************Copyright (c)************************************************                                 
**--------------File Info-----------------------------------------------------------------------------
** File name:			     main.c
** Last modified Date:          
** Last Version:		   
** Descriptions:		   使用的SDK版本-SDK_15.2
**						
**----------------------------------------------------------------------------------------------------
** Created by:			
** Created date:		2019-1-16
** Version:			    1.0
** Descriptions:		2.4G无线通讯试验实验
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
//ESB需要引用的头文件
#include "nrf_esb.h"
#include "nrf_error.h"
#include "nrf_esb_error_codes.h"
#include "sdk_common.h"

/* 试验需要用到IK-52832DK开发板中的指示灯D1和UART，占用的nRF52832引脚资源如下
P0.17：输出：驱动指示灯D1


P0.06：输出：串口TXD
P0.08：输入：串口RXD

需要用跳线帽短接P0.17 P0.06 P0.08
*/

#define UART_TX_BUF_SIZE 256       //串口发送缓存大小（字节数）
#define UART_RX_BUF_SIZE 256       //串口接收缓存大小（字节数）

//static nrf_esb_payload_t        tx_payload;

static nrf_esb_payload_t        rx_payload;

//串口事件回调函数，该函数中判断事件类型并进行处理
void uart_error_handle(app_uart_evt_t * p_event)
{
    //通讯错误事件
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    //FIFO错误事件
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}
//串口初始化配置：波特率115200bps，关闭硬件流控
void uart_config(void)
{
  uint32_t err_code;
	
	//定义串口通讯参数配置结构体并初始化
  const app_uart_comm_params_t comm_params =
  {
    RX_PIN_NUMBER,//定义uart接收引脚
    TX_PIN_NUMBER,//定义uart发送引脚
    RTS_PIN_NUMBER,//定义uart RTS引脚，注意流控关闭后虽然定义了RTS和CTS引脚，但是不起作用
    CTS_PIN_NUMBER,//定义uart CTS引脚
    APP_UART_FLOW_CONTROL_DISABLED,//关闭uart硬件流控
    false,//禁止奇偶检验
    NRF_UART_BAUDRATE_115200//uart波特率设置为115200bps
  };
  //初始化串口，注册串口事件回调函数
  APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

  APP_ERROR_CHECK(err_code);		
}
//ESB事件回调函数
void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    uint8_t i;
	  //判断事件类型
	  switch (p_event->evt_id)
    {
        //发送成功事件
			  case NRF_ESB_EVENT_TX_SUCCESS:
            printf("TX SUCCESS EVENT");
            break;
				//发送失败事件
        case NRF_ESB_EVENT_TX_FAILED:
            printf("TX FAILED EVENT");
            (void) nrf_esb_flush_tx();
            (void) nrf_esb_start_tx();
            break;
				//接收事件
        case NRF_ESB_EVENT_RX_RECEIVED:
            //读取接收的数据和该数据包的RSSI
				    if (nrf_esb_read_rx_payload(&rx_payload) == NRF_SUCCESS)
            {
                //串口打印出接收的数据长度
							  printf("length = %02X  ",(uint8_t)rx_payload.length); 
							  //串口打印出接收的数据
							  printf("DATA = ");
							  for(i=0;i<rx_payload.length;i++)printf(" %02X",(uint8_t)rx_payload.data[i]);  
							  //串口打印出该包数据的RSSI
							  printf("  RSSI = -%d",(uint8_t)rx_payload.rssi);    
							  printf("\r\n");
                nrf_gpio_pin_toggle(LED_1);                 //D1指示灯状态翻转，指示灯接收到新的数据      
            }
            break;
    }
}
//初始化高频时钟，2.4G必须使用高频时钟，而且必须使用外部的32MHz晶体作为时钟源，否则无法保证信号的精度
void clocks_start( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}
//初始化ESB
uint32_t esb_init( void )
{
    uint32_t err_code;
    uint8_t base_addr_0[4] = {0xE4, 0xE3, 0xE2, 0xE1};
    uint8_t base_addr_1[4] = {0xC2, 0xC2, 0xC2, 0xC2};
    uint8_t addr_prefix[8] = {0xE5, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };
    //定义ESB配置结构体，并使用预先定义的默认参数给ESB配置结构体赋值，之后根据需要修改
    nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;
		
		//2.4G协议：ESB，动态数据长度
    nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
		//ESB重发延迟时间：600us
    nrf_esb_config.retransmit_delay         = 600;
		//ESB数据速率：2M
    nrf_esb_config.bitrate                  = NRF_ESB_BITRATE_2MBPS;
		//ESB事件回调函数
    nrf_esb_config.event_handler            = nrf_esb_event_handler;
    //ESB模式：PRX（主接收）
		nrf_esb_config.mode                     = NRF_ESB_MODE_PRX;
    //关闭自动应答
		nrf_esb_config.selective_auto_ack       = true;

    //初始化ESB
    err_code = nrf_esb_init(&nrf_esb_config);
    //检查返回的错误代码
    VERIFY_SUCCESS(err_code);
    //设置地址0
    err_code = nrf_esb_set_base_address_0(base_addr_0);
    VERIFY_SUCCESS(err_code);
    //设置地址1
    err_code = nrf_esb_set_base_address_1(base_addr_1);
    VERIFY_SUCCESS(err_code);
    //设置地址前缀
    err_code = nrf_esb_set_prefixes(addr_prefix, NRF_ESB_PIPE_COUNT);
    VERIFY_SUCCESS(err_code);
		
		//设置信道，注意：发射端和接收端只有处于同一个信道才能传输数据
		//频率 = (2400 + channel) MHz，channel为整数，建议范围  0<channel<83
		err_code = nrf_esb_set_rf_channel(50);

    return err_code;
}
/***************************************************************************
* 描  述 : main函数 
* 入  参 : 无 
* 返回值 : int 类型
**************************************************************************/
int main(void)
{
		uint32_t err_code;
		//初始化开发板上的4个LED，即将驱动LED的GPIO配置为输出，
		bsp_board_init(BSP_INIT_LEDS);
		//初始化串口
		uart_config();

		clocks_start();

		err_code = esb_init();
		APP_ERROR_CHECK(err_code);
		err_code = nrf_esb_start_rx(); //启动ESB接收

		while(true)
		{
 	
		
  }
}
/********************************************END FILE**************************************/
