# AVRDUDE, fuses, opcode

## 1. Programmer, AVR Microcontroller - First Connection

### 1.1 USBasp

As a programmer I will use USBasp - USB programmer for Atmel AVR controllers (see https://www.fischl.de/usbasp/). USBasp is a USB in-circuit programmer for Atmel AVR controllers. It simply consists of an ATMega88 or an ATMega8 and a couple of passive components. The programmer uses a firmware-only USB driver, no special USB controller is needed.  
It is possible to build your own programmer, or buy already manufactured device, for now I prefer option #2.  

After connecting the programmer to a USB port I need to chech the USBasp device:  
`lsusb`  

I see the following output:  
#### Bus XXX Device YYY: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb

I am interesting in vendorId:productId pair, it should be '16c0:05dc'.  

### 1.2 BIN utilities

It also includes commands for working with binary and hexadecimal files, dumping memory sections, and handling different file formats.

To work with binary and hexidecimal files:  
`hexdump -C <fileName>`  
`xxd <fileName>`  
`hexedit <fileName>`  

### 1.2 AVRDUDE

This section provides instructions for setting up and verifying a connection to an AVR microcontroller using the AVRDUDE utility.  

Then, I need to install downloader-uploader:  
`sudo apt install avrdude`   

To check connection with the AVR controller:  
`avrdude -c usbasp-clone -p m1284`  
`avrdude -c usbasp-clone -p m1284 -v` verbose output (to get more info add more -v flags)  

Let's dump all available memory sections:  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U flash:r:flash_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U lfuse:r:lfuse_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U hfuse:r:hfuse_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U efuse:r:efuse_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U lock:r:lock_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U signature:r:signature_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U calibration:r:calibration_dump`  

See http://savannah.nongnu.org/bugs/?44717

Different file formats:  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_raw:r`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_intel:i`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_motorola:s`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_decimal:d`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_hex:h`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_bin:b`  

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
`avrdude -c usbasp-clone -p m1284 -U lfuse:w:0x22:m`  

With the current example you will get something that really similar to the 1MHz pulses, but depending on temperature or supply voltage result value may vary. Just for investigation try to freez the MCU, then check the real frequency on pin 1 port B, and then heat it, and check the frequency again. Moreover, try to change the value of supply voltage (of course do not exceed the maximum voltage, see the datasheet).

Here is some results:  
- t = 28-29 degree Celsius: f = [968 ; 971] kHz;
- t = -3 degree Celsius: f = 49.6 kHz;
- t = 90-92 degree Celsius: f = [50.8 ; 50.9] kHz;
- V = 1.9 volts: f = 47.9 kHz;
- V = 2.5 volts: f = 49.5 kHz;
- V = 3.0 volts: f = 50.0 kHz;
- V = 4.0 volts: f = 50.1 kHz;
- V = 5.0 volts: f = 50.2 kHz;
- V = 5.5 volts: f = 50.2 kHz.

Next, disable the clock prescaler (0010 0010 (0x22) -> 1010 0010 (0xA2)):  
`avrdude -c usbasp-clone -p m1284 -U lfuse:w:0xA2:m`  

Next, configure the controller for full swing oscillator with start-up time 16K CK + 65ms (1010 0010 (0xA2) -> 1011 0111 (0xB7)):  
`avrdude -c usbasp-clone -p m1284 -U lfuse:w:0xB7:m`  

## 3. Opcodes (pure bare metal "Hello World!")

Here is a simpliest bare metal "Hello World" example without standard AVR libraries, and even without compiler. Only opcodes.  

Create the 'firmware.bin' file:  
`touch firmware.bin`  

### 3.1 Led on

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp-clone -p m1284 -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp-clone -p m1284 -e`  

### 3.2 Blink led

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0), and the '00 9A' opcode ('sbi' for PINA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp-clone -p m1284 -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp-clone -p m1284 -e`  

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
