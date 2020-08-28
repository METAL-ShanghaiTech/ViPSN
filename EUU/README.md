# Energy User Unit (EUU)

A programmable BLE SoC (system on chip) nRF52832 by Nordic Inc. serves as the EUU. The EUU has three parts: transceiver, sensor, and CPU. The sensor part uses the on-chip temperature sensor in nRF52832. 
Two remote edge devices are designed for receiving the signals sent out by ViPSN. 
One is a cell phone, which runs a customized mobile app as the EDU module. 
Another is a host PC, which installs a USB BLE receiver module and data processing
program. 
More detailed explanation can be referred to paper ([ViPSN: A Vibration-Powered IoT Platform](../README.md/#divtop)).

## Software

The EUU software includes the following parts:

- Case-1: [intermittent vibrations](./software/EUU_templates/examples/case_of_intermittent_vibrations/pca10040/blank/arm5_no_packs/nrf_pwr_mgmt_pca10040.uvprojx);
- Case-2: [transient excitation](./software/EUU_templates/examples/case_of_transient_excitation/pca10040/blank/arm5_no_packs/nrf_pwr_mgmt_pca10040.uvprojx);
- [Receiver](./software/Receiver/mdk5/esb_rx.uvprojx).

The main differences between case of intermittent vibrations and transient excitation are as follows:

```c
//it has two types of timer, one is being ticked repeating with the interval set before     
err_code = app_timer_create(&m_led_toggle_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                led_toggle_timeout_handler);
```

```c
//the other is being ticked singlely	
err_code = app_timer_create(&m_led_toggle_timer_id,
                               APP_TIMER_MODE_SINGLE_SHOT,
                               led_toggle_timeout_handler);
```

<!-- ## How to install keil5

 Go to [here](http://www2.keil.com/mdk5 ) to download keil5.

It is necessary to activate keil5 before compiling code.

Device is nordic nRF52832-QFAA.

The following pack are required after installing keil5:

1. NordicSemiconductor.nRF_DeviceFamilyPack.8.17.0.pack
2. NordicSemiconductor::Device:Startup:8.9.0
3. ARM.CMSIS.4.5.0

When open [project](.\EUU\software\EUU_trans\examples\case of bridge vibration\pca10040\blank\arm5_no_packs), the dialog box will pop and remind installing above packs. 

After automatically installing, keil5 can complier the project. 

JLINK is recommended to download hex file. If JLINK is not available for developers, STLINK is also available.  -->

<!-- ### Code & Project

In EUU, there are two example projects. 

Developers should build and download it. If something go wrong, please read **Problems may encountered**.

The brief explanation for the project is following:

#### Bridge 

Code can be opened [here](.\EUU\software\EUU_trans\examples\case of bridge vibration\pca10040\blank\arm5_no_packs).

**BUTTON_TOUCH** is the IO port set. 

When **BUTTON_TOUCH** is rising edge, IO interrupt starts. 

When it is falling edge, IO interrupt stops. 

When IO interrupt starts, a timer starts at the same time. 

The timer is set by **LED_TOGGLE_INTERVAL**. 

After timer overflows, **led_toggle_timeout_handler** function is called. 

In this case, it only has a function named **s_tx()**. Developers can change this function to its custom function. 

This function starts high frequency clk at the beginning, then collecting temperature sensor data, sending by ESB, delaying 200ms, and then changing clk from high frequency to low frequency.

In this Bridge case, the timer will repeat according to **LED_TOGGLE_INTERVAL**. And it repeats until IO port is falling edge.



#### Transient 

Code can be opened [here](.\EUU\software\EUU_trans\examples\case of transient excitation\pca10040\blank\arm5_no_packs).

**BUTTON_TOUCH** is the IO port set. 

When **BUTTON_TOUCH** is rising edge, IO interrupt starts. 

When it is falling edge, IO interrupt stops. 

When IO interrupt starts, a timer starts at the same time. 

The timer is set by **LED_TOGGLE_INTERVAL**. 

After timer overflows, **led_toggle_timeout_handler** function is called. Then the timer closes before IO detects it is falling edge. 

In this case, it only has a function named **s_tx()**. Developers can change this function to its custom function. 

This function starts high frequency clk at the beginning, then collecting temperature sensor data, sending by ESB, delaying 200ms, and then changing clk from high frequency to low frequency.


In this Transient case, the timer will only be singly ticked. And it repeats until IO port is falling edge. -->
