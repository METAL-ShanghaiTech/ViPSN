/**
NAME: Xin LI
DATE: 2019-10-01-233045
**/
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

#include "nrf_esb.h"
#include "nrf_error.h"
#include "nrf_esb_error_codes.h"
#include "sdk_common.h"




#define UART_TX_BUF_SIZE 256       //buffer size 
#define UART_RX_BUF_SIZE 256       //buffer size 

//static nrf_esb_payload_t        tx_payload;

static nrf_esb_payload_t        rx_payload;

/*
uart handle error event 
*/
void uart_error_handle(app_uart_evt_t * p_event)
{
    //uart error event
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    //fifo error event
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}


void uart_config(void)//Uart config
{
  uint32_t err_code;
	
  const app_uart_comm_params_t comm_params =
  {
    RX_PIN_NUMBER,//uart received pin
    TX_PIN_NUMBER,//uart transmit pin
    RTS_PIN_NUMBER,//uart RTS pin
    CTS_PIN_NUMBER,//uart CTS pin
    APP_UART_FLOW_CONTROL_DISABLED,
    false,
    NRF_UART_BAUDRATE_115200//baudrate 115200
  };


  APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

  APP_ERROR_CHECK(err_code);		
}


static int r_count = 0;
void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    uint8_t i;
	  
	  switch (p_event->evt_id)
    {
        //success event
			  case NRF_ESB_EVENT_TX_SUCCESS:
            printf("TX SUCCESS EVENT");
            break;
				//failed event
        case NRF_ESB_EVENT_TX_FAILED:
            printf("TX FAILED EVENT");
            (void) nrf_esb_flush_tx();
            (void) nrf_esb_start_tx();
            break;
				//received event
        case NRF_ESB_EVENT_RX_RECEIVED:
            //read received data
				    if (nrf_esb_read_rx_payload(&rx_payload) == NRF_SUCCESS)
            {
								r_count++;
                //print though uart
							  printf("length = %02X  ",(uint8_t)rx_payload.length); 
							  
							  printf("DATA = ");
							  for(i=0;i<rx_payload.length;i++)printf(" %02X",(uint8_t)rx_payload.data[i]);  
							  //Print RSSI
							  printf("  RSSI = -%d",(uint8_t)rx_payload.rssi); 
								printf("  COUNT= %d",r_count);
							  printf("\r\n");
                nrf_gpio_pin_toggle(LED_1);                 //D1 led toggle, receive new data      
							
            }
            break;
    }
}

//init high freq clocks(2.4GHz)
void clocks_start( void )
{
//	  NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
//    NRF_CLOCK->TASKS_LFCLKSTART = 1;
//    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}

uint32_t esb_init( void )//esb init setting
{
    uint32_t err_code;
	  
    uint8_t base_addr_0[4] = {0xE4, 0xE3, 0xE2, 0xE1};
    uint8_t base_addr_1[4] = {0xC2, 0xC2, 0xC2, 0xC2};
    uint8_t addr_prefix[8] = {0xE5, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };
    nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;	
    nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
    nrf_esb_config.retransmit_delay         = 600;//delay of retransmit 600us
    nrf_esb_config.bitrate                  = NRF_ESB_BITRATE_2MBPS;//transmit bitrate 2M   
    nrf_esb_config.event_handler            = nrf_esb_event_handler;
    nrf_esb_config.mode                     = NRF_ESB_MODE_PTX;
    nrf_esb_config.selective_auto_ack       = true;
    err_code = nrf_esb_init(&nrf_esb_config);
    VERIFY_SUCCESS(err_code);
    err_code = nrf_esb_set_base_address_0(base_addr_0);
    VERIFY_SUCCESS(err_code);
    err_code = nrf_esb_set_base_address_1(base_addr_1);
    VERIFY_SUCCESS(err_code);
    err_code = nrf_esb_set_prefixes(addr_prefix, NRF_ESB_PIPE_COUNT);
    VERIFY_SUCCESS(err_code);
		err_code = nrf_esb_set_rf_channel(50);
    return err_code;
}

int main(void)
{
		uint32_t err_code;
		//Gpio led driver
		bsp_board_init(BSP_INIT_LEDS);
		
		uart_config();

		clocks_start();

		err_code = esb_init();
		APP_ERROR_CHECK(err_code);
		err_code = nrf_esb_start_rx(); 
		printf("vipsn receiver ok.\r\n");
		while(true)
		{
 	
		
		}
}
/********************************************END FILE**************************************/
