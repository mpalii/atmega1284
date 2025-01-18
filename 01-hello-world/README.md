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
`avrdude -c usbasp-clone -p m1284 -v -U flash:r:flash_dump`  
`avrdude -c usbasp-clone -p m1284 -v -U eeprom:r:eeprom_dump`  
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

## 2. First Firmware

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
- [AVR® Instruction Set Manual](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)  

