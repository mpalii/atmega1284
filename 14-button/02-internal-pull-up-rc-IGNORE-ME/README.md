### Example 02 - INTERNAL PULL-UP resistor is used; R = 20kΩ and C = 1µF is used for debouncing  

**REALTIME:** The start is incorrect - after startup system will show not 0b11111111 but 0b00000000 instead, RC circuit for debounce is fine  

FIX: the capacitor is placed after the internal pull-up resistor, it needs some time to become fully charged, so after internal pull-up resistor activation some delay is needed.  