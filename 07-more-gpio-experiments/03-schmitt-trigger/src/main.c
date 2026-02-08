/**
 * @author Maksym Palii
 * @brief Schmitt trigger
 * @version 1.0
 * @date 2026 February 08
 */

#include <avr/io.h>

#define PIN_ADDRESS PINA
#define PIN_NUMBER  7

int main(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= _BV(DDRA0);

    start:
        if (bit_is_set(PIN_ADDRESS, PIN_NUMBER))
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
