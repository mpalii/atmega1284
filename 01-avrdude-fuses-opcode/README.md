# AVRDUDE, fuses, opcode

## 1. Programmer, AVR Microcontroller - First Connection

### 1.1 USBasp

As a programmer I will use USBasp - USB programmer for Atmel AVR controllers (see https://www.fischl.de/usbasp/). After connecting the programmer to a USB port I need to chech the USBasp device:  
`lsusb`  

I should see the following output:  
`Bus XXX Device YYY: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb`  

The 'vendorId:productId' pair should be '16c0:05dc'.  

### 1.2 BIN utilities

To work with binary and hexidecimal files:  
`hexdump -C <fileName>` display file contents in hexadecimal, decimal, octal, or ascii  
`xxd <fileName>` make a hexdump or do the reverse  
`hexedit <fileName>` make a hexdump or do the reverse  

### 1.3 AVRDUDE

To install downloader-uploader:  
`sudo apt install avrdude`  

To check connection with the AVR controller:  
`avrdude -c usbasp -p m1284` check the connection (execute twice to check for the communication issues)  
`avrdude -c usbasp -p m1284 -B 32kHz` bitclock  
`avrdude -c usbasp -p m1284 -B 32kHz -v` verbose output  
`avrdude -c usbasp -p m1284 -B 32kHz -vvvvv` max verbose  

Let's dump all available memory sections:  
`avrdude -c usbasp -p m1284 -B 32kHz -vvv -U eeprom:r:eeprom_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -vvv -U flash:r:flash_dump` (see http://savannah.nongnu.org/bugs/?44717)  
`avrdude -c usbasp -p m1284 -B 32kHz -vvvv -U flash:r:flash_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U lfuse:r:lfuse_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U hfuse:r:hfuse_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U efuse:r:efuse_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U lock:r:lock_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U signature:r:signature_dump`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U calibration:r:calibration_dump`  

Different file formats:  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:r`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:i` (see https://en.wikipedia.org/wiki/Intel_HEX)  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:s` (see https://en.wikipedia.org/wiki/SREC_(file_format))  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:d`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:h`  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:b`  

## 2. Fuses

In AVR microcontrollers, fuses are special non-volatile configuration bits that control hardware settings of the microcontroller. These settings are stored in dedicated fuse registers and determine key aspects like clock source, bootloader behavior, reset settings, and memory protection.

Fuses are programmed separately from the main flash memory and EEPROM, and they remain unchanged unless explicitly modified using a programmer.  

AVR fuses cannot be changed at runtime from firmware (code execution).  

From the previous commands I found that the values of low, high, and extended feuses are:  
- lfuse: 0x62;  
- hfuse: 0x99;
- efuse: 0xff.

These values correspond the values from datasheet.

Now I want to see the real clock rate (PORTB1) using the bit CKOUT of fuse low byte (0110 0010 (0x62) -> 0010 0010 (0x22)):  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U lfuse:w:0x22:m`  

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

## 3. Opcodes (pure bare metal "Hello World!")

Here is a simpliest bare metal "Hello World" example without standard AVR libraries, and even without compiler. Only opcodes.  

Create the 'firmware.bin' file:  
`touch firmware.bin`  

### 3.1 Led on

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp -p m1284 -B 32kHz -v -e`  

### 3.2 Blink led

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0), and the '00 9A' opcode ('sbi' for PINA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp -p m1284 -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp -p m1284 -e`  

### 4. Remove AVRDUDE manually installed from sources  

`cd avrdude/build_linux`  
`cat install_manifest.txt`  
`xargs sudo rm -f < install_manifest.txt`  
`which avrdude`  

### See also:  
- [AVRDUDE - AVR Downloader/Uploader (old)](https://www.nongnu.org/avrdude/)  
- [AVRDUDE Online Documentation](https://avrdudes.github.io/avrdude/)  
- [AVRDUDE GIT repository](https://github.com/avrdudes/avrdude)  
- [AVRDUDE wiki](https://github.com/avrdudes/avrdude/wiki)  
- [8. AVR memories](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1184896)  
- [27. Memory programming](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1182132)  
- [14.2.2 Toggling the pin](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1057978)  
- [AVR® Instruction Set Manual](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [7.2.1 megaAVR® Devices](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e48916)  
- [SBRS – Skip if Bit in Register is Set](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e41641)  
- [CLR – Clear Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e23131)  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)  
- [What is the difference between /opt and /usr/local?](https://unix.stackexchange.com/questions/11544/what-is-the-difference-between-opt-and-usr-local)  
- [/usr/bin vs /usr/local/bin on Linux](https://unix.stackexchange.com/questions/8656/usr-bin-vs-usr-local-bin-on-linux)  
