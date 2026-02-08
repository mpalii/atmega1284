/**
 * @author Maksym Palii
 * @brief Pin's internal resistance
 * @version 1.0
 * @date 2026 February 08
 */

#include <avr/io.h>

int main(void)
{
    // Configure data direction for pin 0 and pin 7 (port A) as OUTPUT
    DDRA |= _BV(DDRA0) | _BV(DDRA7);
    // Set pin 7 (port A) driven HIGH
    PORTA |= _BV(PORTA7);

    // Configure data direction for pin 0 and pin 7 (port B) as OUTPUT
    DDRB |= _BV(DDRB0) | _BV(DDRB7);
    // Set pin 0 and pin 7 (port B) driven HIGH
    PORTB |= _BV(PORTB0) | _BV(PORTB7);


    while (1)
    {
        // NOP
    }    

    return 0;
}
