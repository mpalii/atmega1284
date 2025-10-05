/**
 * @author Maksym Palii
 * @brief POV - persistence of vision
 * @version 1.0
 * @date 2025 October 01 
 */

#define F_CPU (8000000UL)

unsigned char message[] = 
{
    0b00000000,
    0b00100010,
    0b00100010,
    0b00000000,
    0b00000000,
    0b01000001,
    0b00100010,
    0b00011100,
    0b00000000


    // // H
    // 0b00000000,
    // 0b01111111,
    // 0b00001000,
    // 0b00001000,
    // 0b00001000,
    // 0b01111111,
    // 0b00000000,

    // // e
    // 0b00001110,
    // 0b00010101,
    // 0b00010101,
    // 0b00010101,
    // 0b00001100,
    // 0b00000000,

    // // l
    // 0b00000000,
    // 0b01000001,
    // 0b01111111,
    // 0b00000001,
    // 0b00000000,
    // 0b00000000,

    // // l
    // 0b00000000,
    // 0b01000001,
    // 0b01111111,
    // 0b00000001,
    // 0b00000000,
    // 0b00000000,

    // // o
    // 0b00001110,
    // 0b00010001,
    // 0b00010001,
    // 0b00010001,
    // 0b00001110,
    // 0b00000000
};

#include <avr/io.h>
#include <stdbool.h>      
#include <util/delay.h>

static inline void init_io_pins(void)
{
    // Configure data direction for port C as OUTPUT
    DDRC = 0xFF;
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= _BV(DDA0);
}

int main(void) 
{
    init_io_pins();

    while (true)
    {
        PORTA &= ~_BV(PA0);
        for (int i = 0; i < 9; i++)
        {
            PORTC = message[i];
            _delay_ms(10);
        }

        PORTA |= _BV(PA0);
        _delay_ms(500-90);
    }
}   
  