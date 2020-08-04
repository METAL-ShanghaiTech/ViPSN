# ViPSN
<img src="https://i.loli.net/2020/05/02/XJesUQ3pP9yd42R.png" alt="ViPSN"  align="right" width="35%">

ViPSN is a vibration-powered sensing node as a programmable IoT platform for battery-free sensing and transmitting. It leverages the exploitation and utilization of ambient vibration energy by using a piezoelectric transducer. The study on ViPSN provides a new paradigm for the design and operation of the battery-free IoT systems based on vibration energy harvesting technology. It encapsulates four units: the vibration source unit (**VSU**), interface circuit unit (**ICU**), energy management unit (**EMU**), and energy user unit (**EUU**).


## System overview
![overview.png](https://i.loli.net/2020/04/30/s5OMEFiSyvnZmGj.png)
The **VSU** is composed of two parts: transducer and vibrator. The piezoelectric transducer is made of a circular low-cost piezoelectric buzzer, whose rim is fixed on the moving part of the resonant speaker. A mass is bonded in the center of the round-shape transducer. A commercial resonant speaker serves as the vibrator, which is utilized to generate the vibrations according to the records from real-world environments. Different from normal speaker architecture, it does not have a traditional diaphragm. It produces sounds by vibrating the large scale hard medium. In other words, the resonant speaker can convert the audio signal into structural vibration.

Under the excitation, the piezoelectric transducer outputs an irregular fluctuating voltage, the **ICU** can be connected for converting the voltage into dc, in order to power the digital electronics. 

For **EMU**, beyond the commercial regulation chip, our design not only provides temporary capacitive energy storage for the extra harvested energy and supplies power at a constant voltage to EUU. It can also produces necessary energy-level indicating signals to the energy user for better operation under fluctuating or intermittent vibrations. A bluetooth low energy sensor node is used to carry out sensing and transmitting functions as **EUU**.

## Prerequisites

### Hardware design
- Altium Designer (version 16.1 or above) is used for the PCB design.
- Solidworks(version 2018 or above) is used for 3D-printer case.
### Software design
- Keil5 is required to compile the software. 

## Software Provided 

In **VSU** folder, this project provides the [Audio](./VSU/Audio/Example) file, which is played by resonant speaker. [AudioGenerator](./VSU/Audio/AudioGenerator.m) can be edited to generate a stable audio wave and . Also, the 3D model file is provided. More details are shown in [VSU README.md](./VSU/README.md).

In **ICU** folder, here are four types circuit model, SEH, SP-P-SSHI, SP-SECE, SP-S-SSHI.

In **EMU** folder, here is a PCB file.

In **EUU** folder, this project provides the [Transmitter Part](.\EUU\software\EUU_trans\examples) and [Receive Part](.\EUU\software\Receiver). And [PCB file](.\EUU\pcb) is also included. 


## For developers
### How to install keil5

 Go to [here](http://www2.keil.com/mdk5 ) to download keil5.

It is necessary to activate keil5 before compiling code.

Device is nordic nRF52832-QFAA.

The following pack are required after installing keil5:

1. NordicSemiconductor.nRF_DeviceFamilyPack.8.17.0.pack
2. NordicSemiconductor::Device:Startup:8.9.0
3. ARM.CMSIS.4.5.0

When open [project](.\EUU\software\EUU_trans\examples\case of bridge vibration\pca10040\blank\arm5_no_packs), the dialog box will pop and remind installing above packs. 

After automatically installing, keil5 can complier the project. 

JLINK is recommended to download hex file. If JLINK is not available for developers, STLINK is also available. 

### Code & Project

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


In this Transient case, the timer will only be singly ticked. And it repeats until IO port is falling edge.




### PCB model

In this project, there are some PCB files. It is easier for developers to change these models for there special requirements. 

For example, if people need to have another line or pin to do some tasks, they can use this as a template.

The first PCB is EMU and the second PCB is EUU. ICU PCB files are shown in [ICU Readme](./ICU/README.md).![emu_pcb.png](https://i.loli.net/2020/07/28/glvrNj16mMwG8PA.png)

![euu_pcb.png](https://i.loli.net/2020/07/30/ZUkPE4gstoIHeVX.png)

### Hardware connection

Piezoelectric transducer-> EMU PZ

EUU Power+ -> EMU LTC3588 Vout

EUU Power- -> EMU LTC3588 GND_h

EMU MIC841 EXTI -> EUU BUTTON_TOUCH

The gjump and vjump (in EMU) should be connected.

If developers want to download hex file into MCU, connecting JLINK to EUU right-bottom.



### How to decide resistance value in PCB

MIC841 comparator has two thresholds. According to its datasheet, low-voltage and high-voltage thresholds can be computed by:

![tem.png](https://i.loli.net/2020/08/04/bWqpYTrogd6CGHn.png)

So the intermittent can be caused after the MCU works within 1 second and its $V_{IN(LO)}$ is lower than MCU power voltage. It works. More details are shown in  MIC841 [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/20005758A.pdf).


### Solidworks model  
These following 3D models are connected to speakers. 

![vsu_2.png](https://i.loli.net/2020/07/30/zgLTpl98fEGJMBr.png)

![vsu_1.png](https://i.loli.net/2020/07/30/EHKzJLeBUgjndk2.png)








## Problems may encountered 

1. In Nordic MCU, user may notice that their power cost is dramatically larger than the paper mentioned. The possible reason is the MCU is broken so that it can not change into low power mode.
2. If user can not open Solidworks file, the possible reason is that the version of Solidworks does not match. It may be lower than the version.
3.  If MIC841 doesn't output automatically, developers can change another group of resistances. Please make sure the value of threshold is correct. (From MIC841 [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/20005758A.pdf))


## Related publications
- Xin Li, Li Teng, Hong Tang, and Junrui Liang*, "ViPSN: A Vibration-Powered IoT Platform", IEEE Internet of Things Journal, under review. <a name="divtop"></a>
- Xin Li, Hong Tang, and Junrui Liang*, “System design and implementation of a transient-motion-powered IoT sensor node”, Proceedings of the ASME 2020 Conference on Smart Materials, Adaptive Structures and Intelligent Systems, Irvine, CA, USA, September 14–16, 2020. (SMASIS 2020).
- Xin Li, Hong Tang, Junrui Liang*, and Lihua Tang, "Exploring the magnetic plucking motion towards a transient-motion-powered IoT sensor node", Proceedings of SPIE Conference 11376, Active and Passive Smart Structures and Integrated Systems IX, 113761U, 22 April 2020. (SPIE SS/NDE 2020).
- Kang Zhao, Yuheng Zhao, and Junrui Liang*, “Live Demo of A Vibration-Powered Bluetooth Sensor with Running PFC Power Conditioning”, Proceedings of the 2017 IEEE International Symposium on Circuits and Systems, Baltimore, USA, May 2017. (ISCAS 2017).
- Kang Zhao, Yuheng Zhao, and Junrui Liang*, “A vibration-powered Bluetooth wireless sensor node with running PFC power conditioning”, Proceedings of the 2017 IEEE International Symposium on Circuits and Systems, Baltimore, USA, May 2017. (ISCAS 2017).

## Contributors
- Yuheng Zhao and Kang Zhao contributed early on to the hardware designs in 2017.
- Xin Li proposed and designed the system of ViPSN in 2019. Hong Tang implemented the hardwares of ICU and EMU, Li Teng and Jingying Chen helped with some important works of EMU and VSU.
- Prof. Junrui Liang oversaw, funded, and originated the project.

## Funding
This research was supported by the grants from the National Natural Science Foundation of China (Project No. 61401277) and ShanghaiTech University (Project No. F-0203-13-003).



## License



---
## Contact
If you have technical problems, please contact: lixin1@shanghaitech.edu.cn or tanghong@shanghaitech.edu.cn.

For business cooperation, please contact: liangjr@shanghaitech.edu.cn.
