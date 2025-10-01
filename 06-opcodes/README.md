### Opcodes (pure bare metal "Hello World!")

### 1. BIN utilities

To work with binary and hexidecimal files:  
`hexdump -C <fileName>` display file contents in hexadecimal, decimal, octal, or ascii  
`xxd <fileName>` make a hexdump or do the reverse  
`hexedit <fileName>` make a hexdump or do the reverse  

Here is a simpliest bare metal "Hello World" example without standard AVR libraries, and even without compiler. Only opcodes.  

Create the 'firmware.bin' file:  
`touch firmware.bin`  

### 2. Led on

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp -p m1284 -B 32kHz -v -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp -p m1284 -B 32kHz -v -e`  

### 3. Blink led

With **hexedit** add the '08 9A' opcode ('sbi' for DDRA register, pin 0), and the '00 9A' opcode ('sbi' for PINA register, pin 0).  

Upload the firmware with the following command:  
`avrdude -c usbasp -p m1284 -U flash:w:firmware.bin:r`  

To erease the chip use the next command:  
`avrdude -c usbasp -p m1284 -e`  

### See also:  
- [8. AVR memories](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1184896)  
- [27. Memory programming](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1182132)  
- [14.2.2 Toggling the pin](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1057978)  
- [AVR® Instruction Set Manual](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [7.2.1 megaAVR® Devices](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e48916)  
- [SBRS – Skip if Bit in Register is Set](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e41641)  
- [CLR – Clear Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e23131)  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
