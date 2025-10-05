/**
 * @author Maksym Palii
 * @brief Schmitt trigger
 * @version 1.0
 * @date 2025 October 03
 */

#include <avr/io.h>
#include <stdbool.h>      

static inline void init_io_pins(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= 1 << DDRA0;
}

int main(void) 
{
    init_io_pins();

    while (true)
    {
        int input = PINB & (1 << PB0);
        if (input)
        {
            PORTA &= ~(1 << PA0);
        }
        else
        {
            PORTA |= (1 << PA0);
        }
    }
}   
  