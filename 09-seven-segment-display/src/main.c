/**
 * @author Maksym Palii
 * @brief seven-segment display, static lighting
 * @date 2026 August 27
 */

#define F_CPU (8000000UL)
#define COMMON_CATHODE_MODE

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

/*
 * The DIGITS array stores values for displaying the digits 0-F to a seven-segment display.
 *
 * The index of the array element is equivalent to a digit in hexadecimal form,
 * each array element stores the state of the seven-segment port for this digit. 
 */
const uint8_t DIGITS[] = {
    #if (!defined(COMMON_ANODE_MODE) && !defined(COMMON_CATHODE_MODE))
    #error "Connection mode is not specified!"
    #endif

    #ifdef COMMON_CATHODE_MODE
        0b00111111,		// 0
        0b00000110,		// 1
        0b01011011,		// 2
        0b01001111,		// 3
        0b01100110,		// 4
        0b01101101,		// 5
        0b01111101,		// 6
        0b00000111,		// 7
        0b01111111,		// 8
        0b01101111,		// 9
        0b01110111,		// A (decimal 10)
        0b01111100,		// B (decimal 11)
        0b00111001,		// C (decimal 12)
        0b01011110,		// D (decimal 13)
        0b01111001,		// E (decimal 14)
        0b01110001		// F (decimal 15)
    #endif

    #ifdef COMMON_ANODE_MODE
        (uint8_t) ~0b00111111,		// 0
        (uint8_t) ~0b00000110,		// 1
        (uint8_t) ~0b01011011,		// 2
        (uint8_t) ~0b01001111,		// 3
        (uint8_t) ~0b01100110,		// 4
        (uint8_t) ~0b01101101,		// 5
        (uint8_t) ~0b01111101,		// 6
        (uint8_t) ~0b00000111,		// 7
        (uint8_t) ~0b01111111,		// 8
        (uint8_t) ~0b01101111,		// 9
        (uint8_t) ~0b01110111,		// A (decimal 10)
        (uint8_t) ~0b01111100,		// B (decimal 11)
        (uint8_t) ~0b00111001,		// C (decimal 12)
        (uint8_t) ~0b01011110,		// D (decimal 13)
        (uint8_t) ~0b01111001,		// E (decimal 14)
        (uint8_t) ~0b01110001		// F (decimal 15)
    #endif
};

int main(void)
{
    // Configure data direction for pins 0-7 (port D) as OUTPUT
    DDRD |= 0xFF;
	
    // Set port D state to display digit
    while (true) 
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            PORTD = DIGITS[i];
            _delay_ms(1000);
        }

        for (int8_t i = 15; i >= 0; i--)
        {
            PORTD = DIGITS[i];
            _delay_ms(500);
        }
    }
}