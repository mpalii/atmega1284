/**
 * @author Maksym Palii
 * @brief Button with internal PULL-UP resistor, no debounce
 * @version 1.0
 * @date 2026 February 13
 */

#include <avr/io.h>
#include <stdbool.h>

int main(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT - Built-in LED
    DDRA |= _BV(DDRA0);
    // Configure data direction for port C as OUTPUT - LEDs bar
    DDRC = 0xFF;
    // Enable internal pull-up resistor pin 7 (port A) - Button
    PORTA |= _BV(PORTA7);

    bool button_was_pressed = false;
    unsigned char counter = 0;

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
        }
    }

    return 0;
}