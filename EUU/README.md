# EUU

A programmable nRF52832 BLE SoC serves as the EUU. 
It is based on an ARM Cortex-M4 CPU with the floating-point unit running at 64 MHz.
And another nRF52832 node is programmed as a host to receive the packet from ViPSN. 
More detailed explanation can be referred to paper ([ViPSN: A Vibration-Powered IoT Platform](../README.md/#divtop)).

## Software

The EUU software includes the following parts:

- Case: [bridge vibration](./software/EUU_trans/examples/case of bridge vibration/pca10040/blank/arm5_no_packs/nrf_pwr_mgmt_pca10040.uvprojx);
- Case: [transient excitation](./software/EUU_trans/examples/case of transient excitation/pca10040/blank/arm5_no_packs/nrf_pwr_mgmt_pca10040.uvprojx);
- [Receiver](./software/Receiver/mdk5/esb_rx.uvprojx).



The main difference between Bridge Case and Transient Case is listed following:


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

## PCB

Also we provide pcb file. Developers can open [here](./pcb/euu.PcbDoc) 
<img src="https://i.loli.net/2020/07/30/ZUkPE4gstoIHeVX.png" alt="euu_pcb.png"  />