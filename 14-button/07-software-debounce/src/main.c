/**
 * @author Maksym Palii
 * @brief Button with internal PULL-UP resistor, software debounce
 * @version 1.0
 * @date 2025 October 11
 */

#define F_CPU (8000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h> 

bool button_was_pressed = false;
unsigned char counter = 255;

int main(void)
{
    // Configure data direction for port D as OUTPUT
    DDRC = 0xFF;
    // Enable internal pull-up resistor pin 0 (port D)
    PORTA |= _BV(PORTA7);

    while (true)
    {
        // output result
        PORTC = counter;

        // check whether button was pressed
        if (bit_is_clear(PINA, PINA7) && !button_was_pressed)
        {
            button_was_pressed = true;
            // on press event
            counter++;
        }
        
        // check whether button was released
        if (bit_is_set(PINA, PINA7) && button_was_pressed)
        {
            button_was_pressed = false;
            // on release event
            //NOP
        }

        // simpliest software debounce
        _delay_ms(15);
    }
}
