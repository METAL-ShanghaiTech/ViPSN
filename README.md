# ViPSN
 <img src="https://i.loli.net/2020/05/02/xvV8wqNRm5D9AjQ.png" alt="ViPSN"  align="right" width="35%">
ViPSN is a vibration-powered sensing node as a programmable IoT platform for battery-free sensing and transmitting. It leverages the exploitation and utilization of ambient vibration energy by using a piezoelectric transducer. The study on ViPSN provides a new paradigm for the design and operation of the battery-free IoT systems based on vibration energy harvesting technology. It encapsulates four units: the vibration source unit (**VSU**), interface circuit unit (**ICU**), energy management unit (**EMU**), and energy user unit (**EUU**).


## System overview
![overview.png](https://i.loli.net/2020/04/30/s5OMEFiSyvnZmGj.png)
The **VSU** is composed of two parts: transducer and vibrator. The piezoelectric transducer is made of a circular low-cost piezoelectric buzzer, whose rim is fixed on the moving part of the resonant speaker. A mass is bonded in the center of the round-shape transducer. A commercial resonant speaker serves as the vibrator, which is utilized to generate the vibrations according to the records from real-world environments. Different from normal speaker architecture, it does not have a traditional diaphragm. It produces sounds by vibrating the large scale hard medium. In other words, the resonant speaker can convert the audio signal into structural vibration.

Under the excitation, the piezoelectric transducer outputs an irregular fluctuating voltage, the **ICU** can be connected for converting the voltage into dc, in order to power the digital electronics. 

For **EMU**, beyond the commercial regulation chip, our design not only provides temporary capacitive energy storage for the extra harvested energy and supplies power at a constant voltage to EUU. It can also produces necessary energy-level indicating signals to the energy user for better operation under fluctuating or intermittent vibrations. A bluetooth low energy sensor node is used to carry out sensing and transmitting functions as **EUU**.

## Prerequisites
#### Hardware design
- Altium Designer (version 16.1) is used for the PCB design.
- Solidworks is used for 3D-printer case.
#### Software design
- Keil is requried to compile the software. 


## Related publications
- Xin Li, Li Teng, Hong Tang, and Junrui Liang*, "ViPSN: A Vibration-Powered IoT Platform", IEEE Internet of Things Journal, under review. <a name="divtop"></a>
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
