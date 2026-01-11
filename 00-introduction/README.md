### Why ATmega1284?

- More functional than ATmega328P: more pins, separate lines for connecting a quartz resonator, and dedicated reset line.  
- Increased memory: 128 KB Flash and 16 KB SRAM - enough to get started with FreeRTOS and implement more complex tasks.  
- Simple AVR architecture: easy to learn, well documented, lots of tutorials and examples in web.  
- Used in [ECE 4760](https://people.ece.cornell.edu/land/courses/ece4760/) (Cornell University), where students build real-world projects using AVR and C - a great base for hands-on learning.  

<div align="center">
  <img src="https://media.microchip.com/silicon-devices/large/atmega1284-s2x.png">
</div>

---

### Overview

1. Product page link [ATmega1284 | Microchip Technology](https://www.microchip.com/en-us/product/ATmega1284).  
2. A brief description of the microcontroller can be found in the [**Introduction**](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G1.2848435) and [**2. Overview**](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1236937) sections.  
3. The pin layout is represented in the [**1. Pin configurations**](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1050997) section.  
4. According to the [**7.2.1 megaAVR® Devices**](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d1951e73901) - ATmega1284 has AVRe+ core (with EIJMP, EICALL missing instructions - these istructions for MCUs with more than 64K words (128 KB) program space).  

---

### See also:
- [Complementary metal–oxide–semiconductor](https://en.wikipedia.org/wiki/CMOS)  
- [Reduced instruction set computer](https://en.wikipedia.org/wiki/Reduced_instruction_set_computer)  
- [What DOES "fully-static operation" really MEAN?](https://www.avrfreaks.net/s/topic/a5C3l000000UCMzEAO/t061347)  
- [AVR201: Using the AVR Hardware Multiplier](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-1631-Using-the-AVR-Hardware-Multiplier_ApplicationNote_AVR201.pdf)  
  - [MUL – Multiply Unsigned](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e34494)  
  - [MULS – Multiply Signed](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e34848)  
  - [MULSU – Multiply Signed with Unsigned](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e35196)  
  - [FMUL – Fractional Multiply Unsigned](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e27576)  
  - [FMULS – Fractional Multiply Signed](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e27948)  
  - [FMULSU – Fractional Multiply Signed with Unsigned](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e28312)  
- [Read While Write Flash Memory on AVR®](https://developerhelp.microchip.com/xwiki/bin/view/products/mcu-mpu/8-bit-avr/structure/read-write-memory/#HBriefAVRReadWhileWriteMemorySummary)  
- [Read While Write (RWW) Memory Explained in a Flash](https://www.microchip.com/en-us/about/media-center/blog/2024/rww-memory-explained-in-a-flash)  
- [Atmel QTouch Library](https://www.microchip.com/en-us/development-tool/atmel-qtouch-library)  
- [Atmel QTouch Library - User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/doc8207.pdf)  
- [Introduction to QTouch® Peripheral Touch Controller (PTC)](https://developerhelp.microchip.com/xwiki/bin/view/applications/touch-gesture/atmel-studio-qtouch-library-composer-legacy/Intro-to-qtouch-ptc/)  
- [JTAG](https://en.wikipedia.org/wiki/JTAG)  
