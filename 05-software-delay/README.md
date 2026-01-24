### Software Delay

- Working mode of AVR microcontrollers is configured with so called 'Fuse Bits'.  
- The device is shipped with the internal RC oscillator at 8.0MHz and with the fuse CKDIV8 programmed, resulting in 1.0MHz system clock.  
- Let's adjust the *Makefile* with two more targets:  
  - fuses-default - resets fuse bits to the initial state;  
  - fuses-no-divider-int-rc - keeps internal RC Oscillator as a source of pulses, but disables clock divider bit, and MCU will be configured for the 8MHz frequency.
- There are two approaches to work with time intervals in microcontrollers: software and hardware. Software approach based on the dummy moving of an instruction pointer in loops (to form delays), hardware approach instead uses built-in hardware timer-counters.  
- First of all disable internal clock divider with:  
`make fuses-no-divider-int-rc`  
- Then, check the REAL frequencies on the pin 0 of port A using oscilloscope and write down the actual results. Here is some values of measurement:  

<div align="center">  

|**Expected frequency**  |**Actual frequency**    |
|:---------------------|:--------------|
|1Hz    |1.04Hz   |
|24Hz   |25.2Hz   |
|50Hz   |52.6Hz   |
|240Hz  |252Hz    |
|50kHz  |50.1kHz  |
|100kHz |95.6kHz  |

</div>

- Some values are not very precise, especially when generating 100kHz signal.  
- After testing the 100kHz take a look at the assembler listing, in particularly `<main>` section:  

```assembly  
...
000000a4 <main>:
  a4:	08 9a       	sbi	0x01, 0	; 1

000000a6 <.L2>:
  a6:	00 9a       	sbi	0x00, 0	; 0
  a8:	8d e0       	ldi	r24, 0x0D	; 13

000000aa <.L1^B1>:
  aa:	8a 95       	dec	r24
  ac:	f1 f7       	brne	.-4      	; 0xaa <.L1^B1>
  ae:	00 00       	nop
  b0:	fa cf       	rjmp	.-12     	; 0xa6 <.L2>
...
```  

- Here we can highlight three parts of a program:  
  1. instruction [a4] - setting DDRA (pin 0) as output;  
  2. instruction [a6] - toggling PORTA (pin 0);  
  3. instructions [a8 ; b0] - delay itself with 'while' loop jump.  

 - Delay "cost" calculation:  
   - `ldi` - runs as 1 cycle, 1 time;  
   - `dec` - runs as 1 cycle, 13 times;  
   - `brne` - runs as 2 cycles instruction 11 times, and as 1 cycle instruction 1 time;  
   - `nop` - runs as 1 cycle, 1 time;
   - `rjmp` - runs as 2 cycles instruction, 2 times.  

- **Total**: (1x1) + (1x13) + (2x11 + 1x1) + (1x1) + (2x2) = 40 "burned" cycles for half period (or 80 cycles for full period).  

---

### See also:  
- [9.2.1 Default Clock Source](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1053045 "Default clock source")  
- [27.2 Fuse Bits](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1082557 "Fuse Bits")  
- [32. Register Summary](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1357951 "36. Register Summary")  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e39988 "SBI – Set Bit in I/O Register")  
- [LDI - Load Immediate](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e32279 "LDI - Load Immediate")  
- [IN - Load an I/O Location to Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e29280 "IN - Load an I/O Location to Register")  
- [EOR - Exclusive OR](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e27283 "EOR - Exclusive OR")  
- [OUT – Store Register to I/O Location](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e36710 "OUT – Store Register to I/O Location")  
- [DEC - Decrement](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e25921 "DEC - Decrement")  
- [BRNE - Branch if Not Equal](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e19059 "BRNE - Branch if Not Equal")  
- [RJMP - Relative Jump](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e38428 "RJMP - Relative Jump")  
- [SBIW - Subtract Immediate from Word](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e40748 "SBIW - Subtract Immediate from Word")  
- [NOP - No Operation](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e35897 "NOP - No Operation")  
- [AVR Fuse Calculator](https://www.engbedded.com/fusecalc/)  
