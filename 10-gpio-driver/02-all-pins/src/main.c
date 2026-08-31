/**
 * @author Maksym Palii
 * @brief 1284 gpio driver - all pins check
 * @date 2026 August 31
 */

#define F_CPU (8000000UL)
#define DELAY_TIME (125UL)
 
#include <stdbool.h>
#include <util/delay.h>
#include "../../drivers/gpio.h"

// #define EXAMPLE_1   // gpio_toggle()
// #define EXAMPLE_2   // sbi_pin()

int main(void) 
{
    while (true)
    {
        #ifdef EXAMPLE_1
        gpio_toggle(_PA0);
        gpio_toggle(_PA1);
        gpio_toggle(_PA2);
        gpio_toggle(_PA3);
        gpio_toggle(_PA4);
        gpio_toggle(_PA5);
        gpio_toggle(_PA6);
        gpio_toggle(_PA7);

        gpio_toggle(_PB0);
        gpio_toggle(_PB1);
        gpio_toggle(_PB2);
        gpio_toggle(_PB3);
        gpio_toggle(_PB4);
        gpio_toggle(_PB5);
        gpio_toggle(_PB6);
        gpio_toggle(_PB7);

        gpio_toggle(_PC0);
        gpio_toggle(_PC1);
        gpio_toggle(_PC2);
        gpio_toggle(_PC3);
        gpio_toggle(_PC4);
        gpio_toggle(_PC5);
        gpio_toggle(_PC6);
        gpio_toggle(_PC7);

        gpio_toggle(_PD0);
        gpio_toggle(_PD1);
        gpio_toggle(_PD2);
        gpio_toggle(_PD3);
        gpio_toggle(_PD4);
        gpio_toggle(_PD5);
        gpio_toggle(_PD6);
        gpio_toggle(_PD7);
        #endif

        #ifdef EXAMPLE_2
        sbi_pin(_PA0);
        sbi_pin(_PA1);
        sbi_pin(_PA2);
        sbi_pin(_PA3);
        sbi_pin(_PA4);
        sbi_pin(_PA5);
        sbi_pin(_PA6);
        sbi_pin(_PA7);

        sbi_pin(_PB0);
        sbi_pin(_PB1);
        sbi_pin(_PB2);
        sbi_pin(_PB3);
        sbi_pin(_PB4);
        sbi_pin(_PB5);
        sbi_pin(_PB6);
        sbi_pin(_PB7);

        sbi_pin(_PC0);
        sbi_pin(_PC1);
        sbi_pin(_PC2);
        sbi_pin(_PC3);
        sbi_pin(_PC4);
        sbi_pin(_PC5);
        sbi_pin(_PC6);
        sbi_pin(_PC7);

        sbi_pin(_PD0);
        sbi_pin(_PD1);
        sbi_pin(_PD2);
        sbi_pin(_PD3);
        sbi_pin(_PD4);
        sbi_pin(_PD5);
        sbi_pin(_PD6);
        sbi_pin(_PD7);
        #endif

        _delay_ms(DELAY_TIME);
    }

    return 0;
}   
  