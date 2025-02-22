# Bare metal "Hello World"

## 1. AVR Microcontroller First Connection

This section provides instructions for setting up and verifying a connection to an AVR microcontroller using the AVRDUDE utility. It also includes commands for working with binary and hexadecimal files, dumping memory sections, and handling different file formats.

First of all, we need to install downloader-uploader:  
`sudo apt install avrdude`   

To work with binary and hexidecimal files:  
`hexdump -C <fileName>`  
`xxd <fileName>`  
`hexedit <fileName>`  

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

Different file formats:  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_raw:r`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_intel:i`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_motorola:s`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_decimal:d`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_hex:h`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump_bin:b`  

## 2. Fuses

From the previous commands I found that valuse of low, high, and extended feuses are:  
- lfuse: 0x62;  
- hfuse: 0x99;
- efuse: 0xff.

These values correspond the values from datasheet.

Now I want to see the real clock rate (PORTB1) using the bit CKOUT of fuse low byte (0110 0010 (0x62) -> 0010 0010 (0x22)):  
`avrdude -c usbasp-clone -p m1284 -U lfuse:w:0x22:m`  

Next, disable the clock prescaler (0010 0010 (0x22) -> 1010 0010 (0xA2)):  
`avrdude -c usbasp-clone -p m1284 -U lfuse:w:0xA2:m`  

Next, configure the controller for full swing oscillator with start-up time 16K CK + 65ms (1010 0010 (0xA2) -> 1011 0111 (0xB7)):  
`avrdude -c usbasp-clone -p m1284 -U lfuse:w:0xB7:m`  


## 3. Pure bare metal "Hello World!"

Here is a simpliest bare metal "Hello World" example without standard AVR libraries, and even without compiler.  

Create the 'firmware' file:  
`touch firmware`  

### 2.1 Led on

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp-clone -p m1284 -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp-clone -p m1284 -e`  

### 2.2 Blink led

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0), and the '00 9A' opcode ('sbi' for PINA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp-clone -p m1284 -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp-clone -p m1284 -e`  

## 3. Remove AVRDUDE manually installed from sources  

`cd avrdude/build_linux`  
`cat install_manifest.txt`  
`xargs sudo rm -f < install_manifest.txt`  
`which avrdude`  

#### See also:  
- [AVRDUDE - AVR Downloader/Uploader (old)](https://www.nongnu.org/avrdude/)  
- [AVRDUDE Online Documentation](https://avrdudes.github.io/avrdude/)
- [AVRDUDE GIT repository](https://github.com/avrdudes/avrdude)  
- [AVRDUDE wiki](https://github.com/avrdudes/avrdude/wiki)  
- [27. Memory programming](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1182132)  
- [AVR® Instruction Set Manual](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)
- [What is the difference between /opt and /usr/local?](https://unix.stackexchange.com/questions/11544/what-is-the-difference-between-opt-and-usr-local)
- [/usr/bin vs /usr/local/bin on Linux](https://unix.stackexchange.com/questions/8656/usr-bin-vs-usr-local-bin-on-linux)  
