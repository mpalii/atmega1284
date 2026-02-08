/**
 * @author Maksym Palii
 * @brief EMI (electromagnetic interference)  
 * @version 1.0
 * @date 2026 February 05
 */

#include <avr/io.h>

int main(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= _BV(DDRA0);

    start:
        // Check the PA7 state
        if (bit_is_set(PINA, PINA7)) 
        {
            PORTA &= (uint8_t) ~_BV(PORTA0);
        }
        else 
        {
            PORTA |= _BV(PORTA0);
        }
    goto start;

    return 0;
}
