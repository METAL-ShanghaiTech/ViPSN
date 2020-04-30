# ViPSN
ViPSN is a vibration-powered sensing node as a programmable IoT platform for battery-free sensing and transmitting. It leverages the exploitation and utilization of ambient vibration energy by using a piezoelectric transducer. The study on ViPSN provides a new paradigm for the design and operation of the battery-free IoT systems based on vibration energy harvesting technology.
It encapsulates four units: the vibration source unit (VSU), interface circuit unit (ICU), energy management unit (EMU), and energy user unit (EUU). 

## VSU
The VSU is composed of two parts: transducer and vibrator.
The piezoelectric transducer is made of a circular low-cost piezoelectric buzzer, whose rim is fixed on the moving part of the resonant speaker.
A mass is bonded in the center of the round-shape transducer. 
This is a typical harvester structure for PEH.
And note that the mass influences the available output power. 
We have done some trial and error for optimizing the resonance frequency by adjusting the mass.
A commercial resonant speaker serves as the vibrator, which is utilized to generate the vibrations according to the records from real-world environments.
Different from normal speaker architecture, it does not have a traditional diaphragm.
It produces sounds by vibrating the large scale hard medium. 
In other words, the resonant speaker can convert the audio signal into structural vibration.
Compared to the expensive professional vibrator, it is a better option for developer working on vibration-powered IoT applications.

## ICU



## Implementation

<table>
    <tr>
        <td>Unit</td> 
        <td colspan="3">Specification</td> 
   </tr>
   <tr>
     <td rowspan="5">VSU</td>
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
    <td>Type</td>
    <td>ADIN-B1BT</td>
  </tr>  
  </table>

