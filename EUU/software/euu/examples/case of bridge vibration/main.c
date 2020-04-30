/**
NAME: Xin LI
DATE: 2019-10-01-233045
**/

#define key_UART 0
#define key_LED 0
#define key_LOG 0
#define BUTTON_TOUCH 3
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "boards.h"
#include "nrf_delay.h"
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
#include "nrf_drv_gpiote.h"
#include "nrf_temp.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_clock.h"
#include "app_timer.h"
#include "app_button.h"
#include "app_gpiote.h"
#include "bsp.h"
#include "bsp_nfc.h"
#include "nordic_common.h"
#include "app_error.h"
#include "nrf_drv_clock.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


static nrf_esb_payload_t        tx_payload;
static nrf_esb_payload_t        rx_payload;
#define UART_TX_BUF_SIZE 256       
#define UART_RX_BUF_SIZE 256 
void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}
void uart_config(void)
{
		uint32_t err_code;
		
		const app_uart_comm_params_t comm_params =
		{
			RX_PIN_NUMBER,
			TX_PIN_NUMBER,
			RTS_PIN_NUMBER,
			CTS_PIN_NUMBER,
			APP_UART_FLOW_CONTROL_DISABLED,
			false,
			NRF_UART_BAUDRATE_115200
		};
		APP_UART_FIFO_INIT(&comm_params,
													 UART_RX_BUF_SIZE,
													 UART_TX_BUF_SIZE,
													 uart_error_handle,
													 APP_IRQ_PRIORITY_LOWEST,
													 err_code);
		APP_ERROR_CHECK(err_code);		
}
void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
			  case NRF_ESB_EVENT_TX_SUCCESS:
            break;
				case NRF_ESB_EVENT_TX_FAILED:
            (void) nrf_esb_flush_tx();
            (void) nrf_esb_start_tx();
            break;
        case NRF_ESB_EVENT_RX_RECEIVED:
            break;
    }
}

void hclocks_start( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}

void lclocks_start( void )
{
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART = 1;
    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);
}
void clocks_ex( void )
{
    NRF_CLOCK->TASKS_HFCLKSTOP = 1;
		NRF_CLOCK->TASKS_LFCLKSTART = 1;
}

uint32_t esb_init( void )
{
    uint32_t err_code;
	  
    uint8_t base_addr_0[4] = {0xE4, 0xE3, 0xE2, 0xE1};
    uint8_t base_addr_1[4] = {0xC2, 0xC2, 0xC2, 0xC2};
    uint8_t addr_prefix[8] = {0xE5, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };
    nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;	
    nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
    nrf_esb_config.retransmit_delay         = 600;
    nrf_esb_config.bitrate                  = NRF_ESB_BITRATE_2MBPS;
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

static void s_tx(void)
{
		int32_t volatile temp=0;
		
				hclocks_start();
				NRF_TEMP->TASKS_START = 1; 
				while (NRF_TEMP->EVENTS_DATARDY == 0){}
				NRF_TEMP->EVENTS_DATARDY = 0;
				temp = (nrf_temp_read() / 4);
				NRF_TEMP->TASKS_STOP = 1;			

				tx_payload.length = 1;
				tx_payload.data[0]= temp;	
				if (nrf_esb_write_payload(&tx_payload) == NRF_SUCCESS)
				{
#if key_UART
					printf("temperature: %d\r\n", (int)temp); 
#endif
				}
				else
				{

				};						
nrf_delay_us(200);
clocks_ex();
}

APP_TIMER_DEF(m_led_toggle_timer_id);                                  
#define LED_TOGGLE_INTERVAL         APP_TIMER_TICKS(1000)  
static void led_toggle_timeout_handler(void * p_context)
{
					s_tx();
}
static void timers_init(void)
{
    ret_code_t err_code;

    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_led_toggle_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                led_toggle_timeout_handler);
	
//	  err_code = app_timer_create(&m_led_toggle_timer_id,
//                                APP_TIMER_MODE_SINGLE_SHOT,
//                                led_toggle_timeout_handler);
	  APP_ERROR_CHECK(err_code);
}

#define BUTTON_DEBOUNCE_DELAY
#define APP_GPIOTE_MAX_USERS
static void button_handler(uint8_t pin_no, uint8_t button_action)
{	
    if(button_action == APP_BUTTON_PUSH)
    {
        switch(pin_no)
        {
            case BUTTON_TOUCH: 
								app_timer_start(m_led_toggle_timer_id, LED_TOGGLE_INTERVAL, NULL);
					
#if key_UART
					read_button = nrf_gpio_pin_read(BUTTON_TOUCH);	
					printf("read_button: %d\r\n", (int)read_button); 
#endif
            default:
                break;
        }
    }
		if(button_action == APP_BUTTON_RELEASE)
		{
        switch(pin_no)
        {
						case BUTTON_TOUCH:
								clocks_ex();
								app_timer_stop(m_led_toggle_timer_id);
#if key_UART
								printf("TOUCH release\n");
#endif
                break;
            default:
                break;
				}
		}
}

int main(void)
{	
#if key_LOG
		NRF_LOG_INIT(NULL);
		NRF_LOG_DEFAULT_BACKENDS_INIT();
#endif
#if key_UART
		uart_config();
		printf("hello world\r\n");
#endif
#if key_LED
		bsp_board_init(BSP_INIT_LEDS);
#endif
	
		timers_init();
		lclocks_start();
		esb_init();
	  nrf_temp_init(); 

		static app_button_cfg_t p_button[] = { {BUTTON_TOUCH, APP_BUTTON_ACTIVE_HIGH, NRF_GPIO_PIN_NOPULL, button_handler} };
    APP_GPIOTE_INIT(APP_GPIOTE_MAX_USERS);
    app_button_init(p_button, sizeof(p_button) / sizeof(p_button[0]), BUTTON_DEBOUNCE_DELAY);                               									
    app_button_enable();

		while(true)
    {					
					//Put CPU to sleep while waiting for interrupt to save power
					__WFI();
    }	
}
