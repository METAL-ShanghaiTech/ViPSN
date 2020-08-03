/**
NAME: Xin LI
DATE: 2019-10-01-233045
BRIEF:
BUTTON_TOUCH 是设置的中断的IO口，
上升沿的时候触发中断，下降沿的时候中断停止触发，
触发中断之后,定时器开始计时，计时的间隔为LED_TOGGLE_INTERVAL，
在定时器溢出之后，调用led_toggle_timeout_handler函数，即s_tx(),
s_tx()函数先启用高频时钟，
然后用温度传感器采集温度信息，通过ESB发送，
延时200ms，再从高频时钟调整成低频时钟

BUTTON_TOUCH is the IO port set. 
When BUTTON_TOUCH is rising edge, IO interrupt starts. 
When it is falling edge, IO interrupt stops. 
When IO interrupt starts, a timer starts at the same time. 
The timer is set by LED_TOGGLE_INTERVAL. 
After timer overflows, led_toggle_timeout_handler function is called. 
In this case, it only has a function named s_tx(). Developers can change this function to its custom function. 
This function starts high frequency clk at the beginning, then collecting temperature sensor data, sending by ESB, delaying 200ms, and then changing clk from high frequency to low frequency.
In this Bridge case, the timer will repeat according to LED_TOGGLE_INTERVAL. And it repeats until IO port is falling edge.


  
CONNECTION:
Piezoelectric transducer-> EMU PZ
EUU Power+ -> EMU LTC3588 Vout
EUU Power- -> EMU LTC3588 GND_h
EMU MIC841 EXTI -> EUU BUTTON_TOUCH
The gjump and vjump (in EMU) should be connected.

**/

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




#define key_UART 0                                         //宏定义 串口设置 1 是开启 0 是关闭        // macro definition usrt setting 1 is open 0 is close
#define key_LED 0                                          //宏定义 LED设置 1 是开启 0 是关闭        // macro definition LED setting 1 is open 0 is close
#define key_LOG 0                                          //宏定义 JLINK RTT LOG 1 是开启 0 是关闭  // macro definition JLINK RTT LOG 1 is open 0 is close
#define BUTTON_TOUCH 3                                     //BUTTON_TOUCH 是设置的中断的IO口        // BUTTON_TOUCH IO setting 
#define LED_TOGGLE_INTERVAL         APP_TIMER_TICKS(1000)  //发送的间隔时间设置，单位ms              // sending interval setting, unit ms 
//In Bridge Case, we set LED_TOGGLE_INTERVAL about 1000 as a periodic work. Higher the frequency is, heavier the workload is. So it is reasonable setting 



static nrf_esb_payload_t        tx_payload;
#define UART_TX_BUF_SIZE 256       
#define UART_RX_BUF_SIZE 256 
#define BUTTON_DEBOUNCE_DELAY			1 // Delay from a GPIOTE event until a button is reported as pushed. 
#define APP_GPIOTE_MAX_USERS            1  // Maximum number of users of the GPIOTE handler.
APP_TIMER_DEF(m_led_toggle_timer_id);                                  

 

/**@brief
 * 串口发送失败处理函数
 * uart setting error handle function 
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

/**@brief 
 * If uart is available, initialize uart setting for debugger.  
 */
void uart_config(void)
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


/**@brief 
 *
 * @details    
 * ESB发送数据
 * ESB sending data function
 * @param[in]  
 */
void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        //success event
        case NRF_ESB_EVENT_TX_SUCCESS:
                break;
        case NRF_ESB_EVENT_TX_FAILED:
            (void) nrf_esb_flush_tx();
            (void) nrf_esb_start_tx();
            break;
        //fail event
        case NRF_ESB_EVENT_RX_RECEIVED:
            break;
    }
}

/**@brief 
 * 启用高频时钟，以传输数据。
 * start high frequency clk to send data
 * @details    
 * 
 * @param[in]  
 */
void hclocks_start( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}


/**@brief 
 * 启用低频时钟，以节省功耗。
 * start low frequency clk to save power cost
 * @details    
 *
 * @param[in]  
 */
void lclocks_start( void )
{
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART = 1;
    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);
}

/**@brief 
 * 从高频时钟降为低频时钟。
 * change clk from high frequency to low frequency
 * @details    
 *
 * @param[in]  
 */
void clocks_ex( void )
{
    NRF_CLOCK->TASKS_HFCLKSTOP = 1;
    NRF_CLOCK->TASKS_LFCLKSTART = 1;
}

/**@brief 
 * Initialize ESB setting.
 */
uint32_t esb_init( void )
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
/**@brief 
 * 
 * @details    
 * 启用高频时钟，然后用温度传感器采集温度信息，通过ESB发送，延时200ms，再从高频时钟调整成低频时钟
 * start high frequency then temperature sensor collectting data, sent by ESB, delaying 200 ms, changing clk from high frequency to low frequency
 * 
 * @param[in]  
 */
static void s_tx(void)
{
		int32_t volatile temp=0;
		
				hclocks_start();//这里也可以先采集数据再调用高频时钟 //it can also collect first then call high frequency clk 


//  这里是对温度传感器的调用，也可以换成其它自定义的函数
//  it is call for temperature sensor which can be replaced by other usr defined function 
				NRF_TEMP->TASKS_START = 1; 
				while (NRF_TEMP->EVENTS_DATARDY == 0){}
				NRF_TEMP->EVENTS_DATARDY = 0;
				temp = (nrf_temp_read() / 4);
				NRF_TEMP->TASKS_STOP = 1;			
				tx_payload.length = 1;
				tx_payload.data[0]= temp;	
//          
          
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

/**@brief 
 * 定时器溢出后触发事件函数
 * function when timer overflowed
 * @details
 *
 * @param[in]  
 */
static void led_toggle_timeout_handler(void * p_context)
{
					s_tx();
}

/**@brief 
 * Initialize timer for led_toggle_timeout_handler function with APP_TIMER_MODE_REPEATED mode.
 * @details    
 * First, it Initializes app_timer. Then create timer event when timer is out. Here the event is led_toggle_timeout_handler function.
 */
static void timers_init(void)
{
    ret_code_t err_code;

    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
//这里有两种定时方式，一种是一次触发后按照固定的时间间隔重复触发
// it has two types of timer, one is being ticked repeating with the interval set before 
 
    err_code = app_timer_create(&m_led_toggle_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                led_toggle_timeout_handler);
//一种是一次触发后就结束 
// the other is being ticked singlely

//    err_code = app_timer_create(&m_led_toggle_timer_id,
//                                 APP_TIMER_MODE_SINGLE_SHOT,
//                                 led_toggle_timeout_handler);

	  APP_ERROR_CHECK(err_code);
}

/**@brief 
 *
 * @details   
 * 当检测到IO是上升沿的时候，开启定时器。当检测到IO是下降沿的时候，关闭定时器。
 * when detected IO is rising edge, open timer. When detected IO is falling edge, close timer.
 * @param[in]  
 */
static void button_handler(uint8_t pin_no, uint8_t button_action)
{	
    if(button_action == APP_BUTTON_PUSH)//检测按键的状态：这里是摁下，即上升沿 //detect the state of IO: it is touched which is rising edge.
    {
        switch(pin_no)//检测按键IO //detect pin number 
        {
            case BUTTON_TOUCH: 
								app_timer_start(m_led_toggle_timer_id, LED_TOGGLE_INTERVAL, NULL);//开启定时器 //open timer
					
#if key_UART
          uint32_t read_button;
					read_button = nrf_gpio_pin_read(BUTTON_TOUCH);	
					printf("read_button: %d\r\n", (int)read_button); 
#endif
            default:
                break;
        }
    }
		if(button_action == APP_BUTTON_RELEASE)//检测按键的状态：这里是释放，即下降沿 //detect the state of IO: it is released which is falling edge
		{
        switch(pin_no)//检测按键IO //detect pin number
        {
						case BUTTON_TOUCH:
								clocks_ex();
								app_timer_stop(m_led_toggle_timer_id);//关闭定时器 //close timer
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
#if key_LOG//初始化JLINK RTT LOG initialize JLINK RTT LOG 
		NRF_LOG_INIT(NULL);
		NRF_LOG_DEFAULT_BACKENDS_INIT();
#endif
  
#if key_UART//初始化串口 initialize uart
		uart_config();
		printf("hello world\r\n");
#endif
  
#if key_LED//初始化LED io initialize led io
		bsp_board_init(BSP_INIT_LEDS);
#endif
	
    timers_init();//初始化定时器             //Initialize timer
    lclocks_start();//开启低频时钟           //Start low frequency timer 
    esb_init();//esb初始化                  //Initialize ESB
    nrf_temp_init(); //温度传感器检测初始化  //Initialize temperature sensor

    static app_button_cfg_t p_button[] = { {BUTTON_TOUCH, APP_BUTTON_ACTIVE_HIGH, NRF_GPIO_PIN_NOPULL, button_handler} };
    APP_GPIOTE_INIT(APP_GPIOTE_MAX_USERS);
    app_button_init(p_button, sizeof(p_button) / sizeof(p_button[0]), BUTTON_DEBOUNCE_DELAY);                               									
    app_button_enable();//启用按键 //Enable button IO

		while(true)
    {					
					//Put CPU to sleep while waiting for interrupt to save power
					__WFI();
    }	
}
