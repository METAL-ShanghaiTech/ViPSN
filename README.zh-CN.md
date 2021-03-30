# ViPSN 2.0（debug版本）

[English](./README.md) | 简体中文

**ViPSN**（vibration-powered sensing node，振动供能传感节点）是一个面向振动/运动供能传感系统的可编程物联网平台，可以作为振动供能物联网应用的开发平台。

<!-- ## 系统概况 -->

<!-- ## 项目结构 -->

<!--ViPSN为用户提供了振动供能物联网应用开发平台所需要的软硬件资源，整个系统具备良好的可重构性，基于我们提供的资料，用户可根据自己的需求进行个性化定制。ViPSN由四大部分组成：* **EEU**：-->


## 设置和使用

即将推出！目前的（2021-03-05）是ViPSN的debug版本。

现在我们正在努力向ViPSN用户提供硬件，如果需要更多有关信息，请联系作者（email: lixin1@shanghaitech.edu.cn or liangjr@shanghaitech.edu.cn）。

如果您觉得ViPSN对您的研究有帮助，欢迎引用我们的论文：

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

## 先决条件

### 硬件设计

* 本项目硬件部分基于Altium Designer开发，需要9.4或更高版本。

### 软件开发
* 本项目软件部分基于Keil5完成开发工作。

<!-- ### Software Provided 

In **EGU** and **ETU** folders, this project provides the [Audio](./VSU/Audio/Example) file, which is played by resonant speaker. [AudioGenerator](./VSU/Audio/AudioGenerator.m) can be edited to generate a stable audio wave and . Also, the 3D model file is provided. More details are shown in [VSU README.md](./VSU/README.md).

In **EEU** folder, here are four types circuit model, SEH, self-power P-SSHI, self-power SECE, self-power S-SSHI.

In **EMU** folder, here is a PCB file.

In **EUU** folder, this project provides the [Transmitter Part](.\EUU\software\EUU_trans\examples) and [Receive Part](.\EUU\software\Receiver). And [PCB file](.\EUU\pcb) is also included.  -->

## 相关出版物

- Jinxi Zhang, Shaobo Gong, Xin Li, Junrui Liang, Zhong Lin Wang*, and Kailiang Ren*, "A wind‐driven poly (tetrafluoroethylene) electret and polylactide polymer‐based hybrid nanogenerator for self‐powered temperature detection system," Advanced Sustainable Systems, art. no. 2000192. 2021.
- Xin Li, Li Teng, Hong Tang, Haoyu Wang, Yu Liu, Minfan Fu, and Junrui Liang*, “ViPSN: a vibration-powered IoT platform,” IEEE Internet of Things Journal, vol. 8, no. 3, pp. 1728-1739, 2021.
- Xin Li, Hong Tang, Yiyao Zhu and Junrui Liang*, “Power solution of a vibration-powered sensing node,” Proceedings of the 9th International Power Electronics and Motion Control Conference, Nanjing, China, May 31-June 3, 2020. (IPEMC - ECCE Asia 2020).
- Xin Li, Hong Tang, Bao Zhao, and Junrui Liang*, “System design and implementation of a transient-motion-powered IoT sensor node,” Proceedings of the ASME 2020 Conference on Smart Materials, Adaptive Structures and Intelligent Systems, Irvine, CA, USA, September 14–16, 2020. (SMASIS 2020) (Finalist of Best Student Hardware Competision).
- Xin Li, Hong Tang, Junrui Liang*, and Lihua Tang, "Exploring the magnetic plucking motion towards a transient-motion-powered IoT sensor node", Proceedings of SPIE Conference 11376, Active and Passive Smart Structures and Integrated Systems IX, 113761U, 22 April 2020. (SPIE SS/NDE 2020).
- Kang Zhao, Yuheng Zhao, and Junrui Liang*, “Live Demo of A Vibration-Powered Bluetooth Sensor with Running PFC Power Conditioning”, Proceedings of the 2017 IEEE International Symposium on Circuits and Systems, Baltimore, USA, May 2017. (ISCAS 2017).
- Kang Zhao, Yuheng Zhao, and Junrui Liang*, “A vibration-powered Bluetooth wireless sensor node with running PFC power conditioning”, Proceedings of the 2017 IEEE International Symposium on Circuits and Systems, Baltimore, USA, May 2017. (ISCAS 2017).

## 参与本项目的人员

* 赵宇恒和赵康在2017年参与了对本项目早期硬件的设计

- 李鑫在2019年提出ViPSN并进行系统设计
- 汤鸿完成了本项目的硬件部分
- 梁俊睿教授发起，监管本项目并提供经费支持

## 资助

本研究项目受国家自然科学基金（项目编号 61401277）和上海科技大学（项目编号 F-0203-13-003）资助。

## 许可证

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

## 联系我们

如果您对于ViPSN有技术方面的问题，请联系: lixin1@shanghaitech.edu.cn or tanghong@shanghaitech.edu.cn.

商业合作请联系: liangjr@shanghaitech.edu.cn.