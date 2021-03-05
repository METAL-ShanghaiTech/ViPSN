# ViPSN 2.0 (debug version)

**ViPSN** (acronym of vibration-powered sensing node) is a programmable Internet of Things (IoT) platform for the development of vibration- or motion-powered sensing and transmitting systems. It serves as a reconfigurable developing platform for vibration-powered IoT applications.

<!-- ## System overview -->

<!-- ## Project structure -->

## Setup and usage

Coming soon! This is debug version (2021-03-05) of ViPSN. 
Right now we are working on a way to get hardware to users, please contact the authors for more information (email: lixin1@shanghaitech.edu.cn or liangjr@shanghaitech.edu.cn). 
For now, feel **free** to explore the hardware and software designs, but be sure to **cite** our work.
```
@ARTICLE{9169698,
  author={X. {Li} and L. {Teng} and H. {Tang} and J. {Chen} and H. {Wang} and Y. {Liu} and M. {Fu} and J. {Liang}},
  journal={IEEE Internet of Things Journal}, 
  title={ViPSN: A Vibration-Powered IoT Platform}, 
  year={2021},
  volume={8},
  number={3},
  pages={1728-1739},
  doi={10.1109/JIOT.2020.3016993}}
```
## Prerequisites
### Hardware design
- Altium Designer (version 9.4 or above) is used for the PCB design.
### Software design
- Keil5 is required to compile the software. 

<!-- ### Software Provided 

In **EGU** and **ETU** folders, this project provides the [Audio](./VSU/Audio/Example) file, which is played by resonant speaker. [AudioGenerator](./VSU/Audio/AudioGenerator.m) can be edited to generate a stable audio wave and . Also, the 3D model file is provided. More details are shown in [VSU README.md](./VSU/README.md).

In **EEU** folder, here are four types circuit model, SEH, self-power P-SSHI, self-power SECE, self-power S-SSHI.

In **EMU** folder, here is a PCB file.

In **EUU** folder, this project provides the [Transmitter Part](.\EUU\software\EUU_trans\examples) and [Receive Part](.\EUU\software\Receiver). And [PCB file](.\EUU\pcb) is also included.  -->

## Related publications
- Jinxi Zhang, Shaobo Gong, Xin Li, Junrui Liang, Zhong Lin Wang*, and Kailiang Ren*, "A wind‐driven poly (tetrafluoroethylene) electret and polylactide polymer‐based hybrid nanogenerator for self‐powered temperature detection system," Advanced Sustainable Systems, art. no. 2000192. 2021.
- Xin Li, Li Teng, Hong Tang, Haoyu Wang, Yu Liu, Minfan Fu, and Junrui Liang*, “ViPSN: a vibration-powered IoT platform,” IEEE Internet of Things Journal, vol. 8, no. 3, pp. 1728-1739, 2021. <a name="divtop"></a>
- Xin Li, Hong Tang, Yiyao Zhu and Junrui Liang*, “Power solution of a vibration-powered sensing node,” Proceedings of the 9th International Power Electronics and Motion Control Conference, Nanjing, China, May 31-June 3, 2020. (IPEMC - ECCE Asia 2020). <a name="divtop2"></a>
- Xin Li, Hong Tang, Bao Zhao, and Junrui Liang*, “System design and implementation of a transient-motion-powered IoT sensor node,” Proceedings of the ASME 2020 Conference on Smart Materials, Adaptive Structures and Intelligent Systems, Irvine, CA, USA, September 14–16, 2020. (SMASIS 2020) (Finalist of Best Student Hardware Competision).
- Xin Li, Hong Tang, Junrui Liang*, and Lihua Tang, "Exploring the magnetic plucking motion towards a transient-motion-powered IoT sensor node", Proceedings of SPIE Conference 11376, Active and Passive Smart Structures and Integrated Systems IX, 113761U, 22 April 2020. (SPIE SS/NDE 2020).
- Kang Zhao, Yuheng Zhao, and Junrui Liang*, “Live Demo of A Vibration-Powered Bluetooth Sensor with Running PFC Power Conditioning”, Proceedings of the 2017 IEEE International Symposium on Circuits and Systems, Baltimore, USA, May 2017. (ISCAS 2017).
- Kang Zhao, Yuheng Zhao, and Junrui Liang*, “A vibration-powered Bluetooth wireless sensor node with running PFC power conditioning”, Proceedings of the 2017 IEEE International Symposium on Circuits and Systems, Baltimore, USA, May 2017. (ISCAS 2017).

## Contributors
- Yuheng Zhao and Kang Zhao contributed early on to the hardware designs in 2017.
- Xin Li proposed and designed the system of ViPSN in 2019. 
- Hong Tang implemented the hardwares of system.
- Prof. Junrui Liang oversaw, funded, and originated the project.

## Funding
This research was supported by the grants from the National Natural Science Foundation of China (Project No. 61401277) and ShanghaiTech University (Project No. F-0203-13-003).

## License
```
Apache License
Copyright 2020 Xin Li, Hong Tang, and Junrui Liang*, ShanghaiTech University.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
## Contact
If you have technical problems, please contact: lixin1@shanghaitech.edu.cn or tanghong@shanghaitech.edu.cn.

For business cooperation, please contact: liangjr@shanghaitech.edu.cn.
