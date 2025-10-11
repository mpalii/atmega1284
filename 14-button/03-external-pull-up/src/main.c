/**
 * @author Maksym Palii
 * @brief Button with external PULL-UP resistor, R = 20kΩ, no debounce 
 * @version 1.0
 * @date 2025 October 11
 */

#include <avr/io.h>
#include <stdbool.h>

bool button_was_pressed = false;
unsigned char counter = 255;

int main(void)
{
    // Configure data direction for port D as OUTPUT
    DDRC = 0xFF;
    // Keep pin 7 (port A) in Z state (high-impedance)
    // PORTA &= ~_BV(PORTA7);  // default state see datasheet

    while (true)
    {
        // // output result
        PORTC = counter;

        // // check whether button was pressed
        if (bit_is_clear(PINA, PINA7) && !button_was_pressed)
        {
            button_was_pressed = true;
            // on press event
            counter++;
        }
        
        // // check whether button was released
        if (bit_is_set(PINA, PINA7) && button_was_pressed)
        {
            button_was_pressed = false;
            // on release event
            //NOP
        }
    }
}