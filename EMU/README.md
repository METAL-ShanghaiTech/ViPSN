# EMU

<!-- **EMU** plays an essential role to guarantee the robust and reliable operation under complicated vibration conditions.
It is responsible not only for providing temporary capacitive energy storage for the extra harvested energy from **ETU**, but also for supplying power at a constant voltage to **EUU**.
On the other hand, many vibration sources are intermittent, variable, and unpredictable, so vibration-powered devices should operate in various vibration environments, such as intermittent mode or transient mode.
**EMU** has to maximize the harvested energy income from the supply side, minimize the energy dissipation in energy conversion, and properly deliver power on the user’s demand.
The software program should be carried out with an awareness of the stored energy
level.
However, most off-the-shelf commercial regulators IC only emphasized stable logic voltage output.
Necessary interactions between energy storage and EUU were not sufficiently supported.
For example, LTC3588 (Linear Technology Co.) integrates a low-loss full-wave bridge rectifier and a high-efficiency buck converter for PEH power conditioning.
Its power good output pin (PGOOD) is actually used for indicating the availability of stable output voltage, rather than the stored energy level. -->

In this project, an enhanced EMU is developed by making complementary design to the off-the-shelf commercial regulator. 
It produces necessary energy-level indicating signals to the energy user for better operation under fluctuating or intermittent vibrations.
EMU has three parts: 
1. LTC3588 is used for regulation purpose. Its dc-dc power conversion efficiency is around 80% to 90% under different input voltage, output voltage, and loading current. 
2. MIC841, a micro-power, precision-voltage comparator with adjustable hysteresis is used to provide energy indicating signals.
Via adjusting the resistor network, we can change the threshold of stored energy level so that to carry out different functions.
3. A capacitor is used to store harvested energy.

During the operation, the EMU provides two internal energy-level indicating signals to itself and three external signals to the EUU, such that **ViPSN** can properly handle different tasks. 
P<sub>start</sub> sets when V<sub>store</sub> > 5 V and P<sub>close</sub> sets when V<sub>store</sub> < 3.4 V. 
P<sub>start</sub> starts the dc-dc power conversion of LTC3588. 
P<sub>close</sub> turns off the converter. 
There might be several rounds of lockouts and restarts before the output voltage reaches a stable level, because of the depletion and refill of the storage capacitor. 
Besides the fixed UVLO thresholds, the PGOOD pin of LTC3588 offers further information on the output voltage stability.
The PGOOD pin is logic high when the output voltage of LTC3588 is above 92% of the desired regulation voltage. 
If Vcc falls below this threshold, it turns to logic low. 
It should be noted that PGOOD is not a storage-level indicating signal. 
P<sub>good</sub> added in this study provides a real storage-level indicating signal.
It comes with the rising edge of the comparator’s output. 
It denotes that the storage capacitor of EMU has gained sufficient energy to ensure the execution of the most power-consuming atomic operation. 
P<sub>sleep</sub> comes with the falling edge of the comparator’s output. 
It warns that the energy storage of EMU is in shortage; therefore, the EUU must take an emergent process to save the critical data and then go to the ultralowpower deep-sleep mode. 
In addition, via adjusting the resistor network of the comparator, we can change the voltage thresholds for generating P<sub>good</sub> and P<sub>sleep</sub> so as to ensure proper operations under different excitation conditions.

More information about the working principle of EMU can be referred to paper ([ViPSN: A Vibration-Powered IoT Platform](../README.md/#divtop) and [Power solution of a vibration-powered sensing node](../README.md/#divtop2)).

