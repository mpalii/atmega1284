/**
 * @author Maksym Palii
 * @brief 1284 gpio driver - all pins check, loops, array
 * @date 2026 August 31
 */

#define F_CPU (8000000UL)
#define DELAY (500UL)
 
#include <stdbool.h>
#include <util/delay.h>
#include "../../drivers/gpio.h"

const uint8_t pins[] =
{
    _PA0, _PA1, _PA2, _PA3, _PA4, _PA5, _PA6, _PA7, // Port A
    _PB0, _PB1, _PB2, _PB3, _PB4, _PB5, _PB6, _PB7, // Port B
    _PC0, _PC1, _PC2, _PC3, _PC4, _PC5, _PC6, _PC7, // Port C
    _PD0, _PD1, _PD2, _PD3, _PD4, _PD5, _PD6, _PD7  // Port D
};

void gpio_init(void) 
{
    for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
    {
        gpio_set_output(pins[i]);
        // sbi_ddr(pins[i]);   // is not working
    }
}

void set_pins_high(void)
{
    for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
    {
        gpio_high(pins[i]);
        // sbi_port(pins[i]);   // is not working!!!
    }
}

void set_pins_low(void)
{
    for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
    {
        gpio_low(pins[i]);
        // cbi_port(pins[i]);   // is not working!!!
    }
}

int main(void) 
{
    gpio_init();

    while (true)
    {
        set_pins_high();
        _delay_ms(DELAY);     
        set_pins_low();
        _delay_ms(DELAY); 
    }

    return 0;
}   
  