### Timer/Counter 0

- To get most precise timings it is crutual to use hardwart internal timers/counters - Timer/Counter 0 will fit.  
- Timer/Counter 0 related registers:  
  - TCCR0A – Timer/Counter Control Register A;  
  - TCCR0B – Timer/Counter Control Register B;  
  - TCNT0 – Timer/Counter Register (8-bit counter itself);  
  - OCR0A – Output Compare Register A;  
  - OCR0B – Output Compare Register B;  
  - TIMSK 0 – Timer/Counter Interrupt Mask Register;  
  - TIFR0 – Timer/Counter Interrupt Flag Register.  
- With the current example you will get something that really similar to the 25kHz pulses, but depending on temperature or supply voltage result value may vary. 
- Just for investigation try to freez the MCU, then check the real frequency on pin 0 port A, and then heat it, and check the frequency again. Moreover, try to change the value of supply voltage (of course do not exceed the maximum voltage, see the datasheet).  
- These results show that internal RC can't provide accurate timings. Let's adjust our 'Makefile' with the target `fuses-no-divider-ext-clk` which turn off internal prescaler and internal RC, and for now the MCU will look at the external oscillator, so just connect 8MHz crystal with two capacitors as described in the datasheet.  
 - Do the previous experiments again with external crystal. Now it looks really better:)  

 ---

### More experiments  

- Let's adjust our 'Makefile' with the target `fuses-with-divider-ext-osc` which turns on internal prescaler and turns off internal RC;  
- With 8MHz crystal make the fuse CKDIV8 programmed again (to get 1MHz result frequency) or use another 1MHz crystal, and try to generate 25kHz pulses again;  
- Calculate the time for ISR (for this purpose disassemble the code and use AVR instruction set manual);  
- Measure current consumption with internal RC oscillator and external quartz crystal:  
  - Internal RC, with divider 5.0V (1MHz) - current consumption ~9mA;  
  - Internal RC, no divider 5.0V (8MHz) - current consumption ~14mA;  
  - External quartz, no divider (4MHz) - current consumption ~11mA;  
  - External quartz, no divider (8MHz) - current consumption ~13mA;  
  - External quartz, no divider (9.216MHz) - current consumption ~13.5mA;  
  - External quartz, no divider (11.0592MHz) - current consumption ~14.3mA;  
  - External quartz, no divider (18.432MHz) - current consumption ~18mA;  
  - External quartz, no divider (20MHz) - current consumption ~19mA.  

---

### See also:  

- [15. 8-bit Timer/Counter0 with PWM](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1177427 "8-bit Timer/Counter0 with PWM")  
- [7.7.1 Interrupt Response Time](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1184888 "Interrupt Response Time")  
- [9.2 Clock Sources](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1053000 "Clock Sources")  
- [9.3 Low Power Crystal Oscillator](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1322881 "Low Power Crystal Oscillator")  
- [9.4 Full Swing Crystal Oscillator](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1053308 "Full Swing Crystal Oscillator")  
- [9.6 Calibrated Internal RC Oscillator](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1165406 "Calibrated Internal RC Oscillator")  
