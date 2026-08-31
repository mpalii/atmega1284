/**
 * @author Maksym Palii
 * @brief 1284 gpio driver - simple test
 * @date 2026 August 31
 */
 
#include <stdbool.h>
#include "../../drivers/gpio.h"

// #define EXAMPLE_1   // built in led on
// #define EXAMPLE_2   // polling HiZ input
// #define EXAMPLE_3   // polling Pull-UP input

int main(void) 
{
    #ifdef EXAMPLE_1
    gpio_set_output(PA0);
    // sbi_ddr(PA0);
    #endif

    #ifdef EXAMPLE_3
    gpio_high(_PB0);
    // cbi_ddr(_PB0);
    // sbi_port(_PB0);
    #endif

    while (true)
    {
        #if (defined(EXAMPLE_2) || defined(EXAMPLE_3))
        if (gpio_get_input(_PB0)) 
        {
            gpio_set_input(_PA0);
            // cbi_ddr(_PA0);
        }
        else
        {
            // gpio_set_output(_PA0);
            sbi_ddr(_PA0);
        }
        #endif
    }

    return 0;
}   
  