/**
 * @author Maksym Palii
 * @brief Delay loop with 'nop' instruction
 * @version 1.0
 * @date 2026 January 24 
 */ 

#include <avr/io.h>

int main(void) 
{
    // Configure data direction for pins 0 (port A) as OUTPUT (built-in LED)
    DDRA |= _BV(DDRA0);

    while (1)
    {
        // Toggle PA0
        PORTA ^= _BV(PORTA0);

        // Delay (65000 a.k.a. 0xFDE8)
        for (uint16_t i = 0; i < 65000; i++)
        {
            __asm__("nop");
        }
    }
}