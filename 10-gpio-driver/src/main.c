/**
 * @author Maksym Palii
 * @brief 1284 gpio driver test
 * @version 1.0
 * @date 2026 February 21
 */

#define F_CPU (8000000UL)
// #define DELAY (500UL)
 
#include <stdbool.h>
// #include <util/delay.h>
#include "drivers/gpio.h"

// const uint8_t pins[] =
// {
//     // Port A
//     _GPIO_UNUSED_01, _GPIO_UNUSED_02, _GPIO_UNUSED_03, _GPIO_UNUSED_04,
//     _GPIO_UNUSED_05, _GPIO_UNUSED_06, _GPIO_UNUSED_07, _GPIO_UNUSED_08,
//     // Port B
//     _GPIO_UNUSED_09, _GPIO_UNUSED_10, _GPIO_UNUSED_11, _GPIO_UNUSED_12,
//     _GPIO_UNUSED_13, _GPIO_UNUSED_14, _GPIO_UNUSED_15, _GPIO_UNUSED_16,
//     // Port C
//     _GPIO_UNUSED_17, _GPIO_UNUSED_18, _GPIO_UNUSED_19, _GPIO_UNUSED_20,
//     _GPIO_UNUSED_21, _GPIO_UNUSED_22, _GPIO_UNUSED_23, _GPIO_UNUSED_24,
//     // Port D
//     _GPIO_UNUSED_25, _GPIO_UNUSED_26, _GPIO_UNUSED_27, _GPIO_UNUSED_28,
//     _GPIO_UNUSED_29, _GPIO_UNUSED_30, _GPIO_UNUSED_31, _GPIO_UNUSED_32
// };

// void gpio_init(void) 
// {
//     for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
//     {
//         gpio_set_output(pins[i]);
//     }
// }

// void toggle_pins(void)
// {
//     for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
//     {
//         gpio_toggle(pins[i]);
//         // sbi_pin(pins[i]);   // is not working!!!
//     }
// }

int main(void) 
{
    // cbi_ddr(_PB0);
    // sbi_port(_PB0);

    gpio_high(_PB0);

    // gpio_init();
    
    // gpio_set_output(PA0);
    // sbi_ddr(PA0);

    while (true)
    {
        if (gpio_get_input(_PB0)) 
        {
            // gpio_set_input(_PA0);
            cbi_ddr(_PA0);
        }
        else
        {
            // gpio_set_output(_PA0);
            sbi_ddr(_PA0);
        }

        // toggle_pins();

        // gpio_toggle(PA0);
        // sbi_pin(PA0);

        // _delay_ms(DELAY);      
    }

    return 0;
}   
  