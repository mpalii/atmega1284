/**
 * @author Maksym Palii
 * @brief EMI (electromagnetic interference)  
 * @version 1.0
 * @date 2025 October 11
 */

#include <avr/io.h>

int main(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= _BV(DDA0);

    start:
        // Check the PA7 state
        if (bit_is_set(PINA, PINA7)) 
        {
            PORTA |= _BV(PORTA0);
        }
        else 
        {
            PORTA &= ~(_BV(PORTA0));
        }
    goto start;
}
