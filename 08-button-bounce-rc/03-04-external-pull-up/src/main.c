/**
 * @author Maksym Palii
 * @brief Button with external PULL-UP resistor R = 20kΩ (R = 20kΩ and C = 1µF (105) is used for debouncing)  
 * @version 1.0
 * @date 2026 February 14
 */

#include <avr/io.h>
#include <stdbool.h>

int main(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT - Built-in LED
    DDRA |= _BV(DDRA0);
    // Configure data direction for port C as OUTPUT - LEDs bar
    DDRC = 0xFF;
    // Keep pin 7 (port A) in Z state (high-impedance)
    // PORTA &= ~_BV(PORTA7);  // default state see datasheet

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
