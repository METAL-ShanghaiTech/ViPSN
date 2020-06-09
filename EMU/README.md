The EMU has three parts: a DC-DC buck converter, an energy storage capacitor, and a comparator. 
An external comparator is responsible for detecting the energy level of the storage capacitor.
Via adjusting the resistor network, we can change the threshold of stored energy level so that to carry out different functions.
Specially, we use a LTC3588-1 chip for the regulation purpose, it integrates a low-loss full-wave bridge rectifier and a high-efficiency DC-DC buck converter.
We use MIC841, a micro-power, precision-voltage comparator with adjustable hysteresis.
More information about the working principle of EMU can be referred to paper ([ViPSN: A Vibration-Powered IoT Platform](../README.md/#divtop)).