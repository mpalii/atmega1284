### Fuses

In AVR microcontrollers, fuses are special non-volatile configuration bits that control hardware settings of the microcontroller. These settings are stored in dedicated fuse registers and determine key aspects like clock source, bootloader behavior, reset settings, and memory protection.

Fuses are programmed separately from the main flash memory and EEPROM, and they remain unchanged unless explicitly modified using a programmer.  

AVR fuses cannot be changed at runtime from firmware (code execution).  

`avrdude -c usbasp -p m1284 -U lfuse:r:-:h`  
`avrdude -c usbasp -p m1284 -U hfuse:r:-:h`  
`avrdude -c usbasp -p m1284 -U efuse:r:-:h`  

From the previous commands I found that the values of low, high, and extended feuses are:  
- lfuse: 0x62;  
- hfuse: 0x99;
- efuse: 0xff.

These values correspond the values from datasheet.

Now I want to see the real clock rate (PORTB1) using the bit CKOUT of fuse low byte (0110 0010 (0x62) -> 0010 0010 (0x22)):  
`avrdude -c usbasp -p m1284 -v -U lfuse:w:0x22:m`  

With the current example I get something that really similar to the 1MHz pulses, but depending on temperature or supply voltage result value may vary. Just for investigation I will try to freez the MCU, then check the real frequency on pin 1 port B, and then heat it, and check the frequency again. Moreover, I will try to change the value of supply voltage (of course without exceeding the maximum voltage, see the datasheet).

Here is some results:  
- t = 28-30 degree Celsius: f = [968 ; 971] kHz;
- t = -20 degree Celsius: f = ~ 955 kHz;
- t = ~ 75 degree Celsius: f = ~ 997 kHz;
- V = 1.9 volts: f = 974 kHz;
- V = 2.5 volts: f = [978 ; 981] kHz;
- V = 3.0 volts: f = [976 ; 981] kHz;
- V = 4.0 volts: f = [973 ; 977] kHz;
- V = 5.0 volts: f = [969 ; 971] kHz;
- V = 5.2 volts: f = [969 ; 971] kHz.

Next, disable the clock prescaler (0010 0010 (0x22) -> 1010 0010 (0xA2)):  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U lfuse:w:0xA2:m`  

<!-- Next, configure the controller for full swing oscillator with start-up time 16K CK + 65ms (1010 0010 (0xA2) -> 1011 0111 (0xB7)):  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U lfuse:w:0xB7:m`   -->

Put back initial value:  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U lfuse:w:0x62:m`  

### See also:  
- [8. AVR memories](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1184896)  
- [27. Memory programming](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1182132)  
- [14.2.2 Toggling the pin](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1057978)  
- [AVR® Instruction Set Manual](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [7.2.1 megaAVR® Devices](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e48916)  
- [SBRS – Skip if Bit in Register is Set](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e41641)  
- [CLR – Clear Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e23131)  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)  
