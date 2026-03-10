### Interrupt benchmark

- This example demonstrates how to measure the execution time of an external interrupt handler on an AVR microcontroller using Timer/Counter 0.  
- The measured time is displayed using a 74HC595 shift register connected to LEDs.  

---

### Interrupts priority

- This example demonstrates how multiple interrupt sources interact on an AVR microcontroller and how interrupt priority and nesting behave.  
- The program uses:
  - Three external interrupts (`INT0`, `INT1`, `INT2`)
  - One timer overflow interrupt (`TIMER1_OVF`)
- Each interrupt toggles a dedicated LED so that the execution order and nesting behavior can be visually observed.

---

### See also:  

- [7.7.1 Interrupt response time](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1184888)  
- [AVR interrupt response time](https://www.embeddedrelated.com/showthread/comp.arch.embedded/1437-1.php)  
- [Cycle counts to get into ISR](https://www.avrfreaks.net/s/topic/a5C3l000000U9X0EAK/t050436)  
- [How many clk cycles to enter ISR?](https://www.avrfreaks.net/s/topic/a5C3l000000UA1bEAG/t052333)  
