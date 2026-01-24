/**
 * @author Maksym Palii
 * @brief Delay example, visual perception
 * @version 1.0
 * @date 2026 January 24 
 */

/* Before testing disable the system clock prescaler CKDIV8 */
#define F_CPU (8000000UL)

/* Test frequencies for researching */
#define FREQUENCY_1Hz        1  //   1Hz - just a period of one second
#define FREQUENCY_24Hz       24 //  24Hz - frame rate standard for 35mm sound films
#define FREQUENCY_50Hz       50 //  50Hz - AC frequency standard (use camera of a smartphone to see blinking)
#define FREQUENCY_240Hz     240 // 240Hz - display matrix refresh rate 
#define FREQUENCY_50kHz   50000 // 50kHz - something really fast :)
#define FREQUENCY_100kHz 100000 // 100kHz - faster!!!

/* Change the frequency for half-period calculation */
#define HALF_PERIOD (1000000UL / (2UL * FREQUENCY_1Hz))  // us (microseconds)

#include <avr/io.h> 
#include <util/delay.h>

static inline void init_io_pins(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= _BV(DDRA0);
}

int main(void) 
{
    init_io_pins();

    while (1)
    {
        PINA |= _BV(PORTA0);    // pure toggle
        _delay_us(HALF_PERIOD);
    }
}   

