A programmable nRF52832 BLE SoC serves as the EUU. 
It is based on an ARM Cortex-M4 CPU with the floating-point unit running at 64 MHz.
And another nRF52832 node is programmed as a host to receive the packet from ViPSN. 

The EUU software includes the following parts:
- Case: [bridge vibration](./software/euu/examples);
- Case: [transient excitation](./software/euu/examples);
- [Receiver](./software/receiver).