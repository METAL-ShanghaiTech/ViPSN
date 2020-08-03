# VSU

## Brief

The specifications of VSU are listed in this table. The base's 3D printer case is drawn with solidworks, and saved in the folder: [3D](./3D).

<table>
    <tr>
        <td >Unit</td> 
        <td colspan="3">Specification</td> 
   </tr>
   <tr>
     <td rowspan="2">Piezoelectric transducer</td>
     <td>Diameter</td>
     <td>30 mm</td>
  </tr>    
  <tr>
    <td>Material</td>
     <td>PZT sheet on steel</td>
  </tr>
  <tr>
    <td rowspan="2">Mass</td>
     <td>Weight</td>
     <td>13 g</td>
  </tr>
 <tr>
     <td>Material</td>
     <td>Steel</td>
  </tr>
  <tr>
  <td>Resonant speaker</td>
    <td>Manufacturer</td>
    <td>ADIN-B1BT</td>
  </tr>  
  </table>

For the audio file, there are two types. One is a sine wave, the other is simulating from true data measured by an accelerometer. 

## Model

![vsu_1.png](https://i.loli.net/2020/07/30/EHKzJLeBUgjndk2.png)

![vsu_2.png](https://i.loli.net/2020/07/30/zgLTpl98fEGJMBr.png)

## Audio

### Sine wave

#### **Explanation for script:**

The script is named **SineAudioGenerator.m**. It can be opened [here](./Audio/SineAudioGenerator.m).

In this script, we simulate a sine wave. Then the audio file is created by running script.



### Accelerometer Data

Data address：http://eh-network.org/data/

All data is collected [here](./Audio/AccelerometerData). 

For example, [SuspensionBridge_Location_01 Download Address](http://www.holistic.ecs.soton.ac.uk/data/suspension_01/data.zip)

**Original Filename:** SuspensionBridge_Location_01.mat

#### **File Format：**

| time | X_Voltage | Y_Voltage | Z_Voltage | X_Acc | Y_Acc | Z_Acc |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- |
|0.0014	| 1813 |	1589|	1806|	0.00476|	-0.990|	-0.0190|

#### **Test Equipment:**

Custom data logger based on ADXL325 MEMS 3-axis accelerometer

#### **Calibration Parameters:**

**X:** 210 mV/g, zero-g reading 1812 mV
**Y:** 210 mV/g, zero-g reading 1797 mV
**Z:** 210 mV/g, zero-g reading 1810 mV

#### **Axis Directions:**

**X:** horizontal, along the length of the bridge
**Y:** vertically down
**Z:** horizontal, across the bridge

#### **Explanation for file:**

The data streams are included in .mat file, titled with the location of each data segments. There are 7 columns of data that represent: time (in seconds), x-axis raw data (in mV), y-axis raw data (in mV), z-axis raw data (in mV), x-axis acceleration (in g), y-axis acceleration (in g), and z-axis acceleration (in g). The data segments are separated in the time domain by large amplitude motion that can easily be recognised, signalling the beginning and the end of the segment (data logging unit removed from location and rotated).

#### **Explanation for script:**

The script is named **Acc2Aduio.m**. It can be opened [here](./Audio/Acc2Aduio.m).

In this experiment, only time and Z axis direction accelerometer data are required. In other word, the first line and the last line should be picked up in .mat file. 

In this script, we provide code to plot 3 axis accelerations with time.

Then the audio file is created by running script.



