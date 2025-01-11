# AVR Microcontroller Connection Guide 

This guide provides instructions for setting up and verifying a connection to an AVR microcontroller using the AVRDUDE utility. It also includes commands for working with binary and hexadecimal files, dumping memory sections, and handling different file formats.

First of all, we need to install downloader-uploader:  
`sudo apt install avrdude`   

To work with binary and hexidecimal files:  
`hexdump -C <fileName>`  
`xxd <fileName>`  

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

See also:  
- [AVRDUDE - AVR Downloader/Uploader (old)](https://www.nongnu.org/avrdude/)  
- [AVRDUDE Online Documentation](https://avrdudes.github.io/avrdude/)
- [AVRDUDE GIT repository](https://github.com/avrdudes/avrdude)  
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)  

