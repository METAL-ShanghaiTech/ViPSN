# ViPSN 1.0
<img src="https://raw.githubusercontent.com/dremofly/oss/master/uPic/2020-08-29/NShvox.png" alt="ViPSN"  align="right" width="45%">

**ViPSN** (acronym of vibration-powered sensing node) is a programmable Internet of Things (IoT) platform for the development of vibration- or motion-powered sensing and transmitting systems. It serves as a reconfigurable developing platform for vibration-powered IoT applications. The whole set of **ViPSN** assembles six basic modules: a vibration emulator as the energy generation unit (**EGU**); a piezoelectric transducer as the energy transduction unit (**ETU**); a power-boosting interface circuit as the energy enhancement unit (**EEU**); a dc-dc regulator with energy-level indicating signals as the energy management unit (**EMU**); a Bluetooth low energy (BLE) module as the energy user unit (**EUU**); and a mobile app as the edge demonstration unit (**EDU**). All units or modules are connected with easy mechanical joggle joints and electrical plunger pin contacts.


## Prerequisites
### Hardware design
- Altium Designer (version 9.4 or above) is used for the PCB design.
- Solidworks (version 2018 or above) is used for 3D-printer case.
### Software design
- Keil5 is required to compile the software. 

### Specification
<table style="border-collapse: collapse; border: none; border-spacing: 0px;">
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			<b>Unit</b>
		</td>
		<td colspan="3" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			<b>Specification</b>
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			EGU
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Resonant speaker
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Type
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			ADIN-B1BT
		</td>
	</tr>
	<tr>
		<td rowspan="4" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			ETU
		</td>
		<td rowspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Piezoelectric
			<br>
			 transducer
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Diameter
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			30 mm
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Material
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			PZT sheet on steel
		</td>
	</tr>
	<tr>
		<td rowspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Mass
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Weight
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			13 g
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Material
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Steel
		</td>
	</tr>
	<tr>
		<td rowspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			EEU
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			SEH
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Full-wave bridge rectifier
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			SP-SSHI
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Parallel SP-SSHI
		</td>
	</tr>
	<tr>
		<td rowspan="3" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			EMU
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			DC-DC Converter
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			LTC3588-1
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Comparator
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			MIC841
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Storage
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Electrolytic capacitor
		</td>
	</tr>
	<tr>
		<td rowspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			EUU
		</td>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			SoC
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			nRF52832
		</td>
	</tr>
	<tr>
		<td style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			Software
		</td>
		<td colspan="2" style="border-width: 1px; border-style: solid; border-color: rgb(0, 0, 0); text-align: center; padding-right: 3pt; padding-left: 3pt;">
			nRF5 SDK V15.2
		</td>
	</tr>
</table>