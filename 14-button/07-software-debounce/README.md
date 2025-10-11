### Example 07 - Software debounce

The main idea is to increace a time between button pin state cheks. In the current example delay() is used for software debounce, but ideally we should use the button state machine, and hardware timer interrupts to make it non-blocking.

**ANOMALY:** there is a chance that after startup system will show not 0b11111111 but 0b00000000 instead   
**REALTIME:** The start could have anomaly, several hits on the button aren't accompanied by a bounce  