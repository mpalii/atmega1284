/**
 * @author Maksym Palii
 * @brief 74hc595 Example 1 - continuoss pseudo random output
 * @version 1.0
 * @date 2026-02-22
 */

#define F_CPU   (8000000UL)
#define SEED    (17)

#include <stdlib.h>
#include <util/delay.h>
#include "drivers/gpio.h"

int main(void)
{
    // sbi_ddr(_PA0);
    gpio_set_output(_PA0);

    gpio_set_output(SER);
    gpio_set_output(RCLK);
    gpio_set_output(SRCLK);

    srand(SEED);

    while(1)
    {
        char pseudo_random_value = (char) rand();

        // shift data
        for (uint8_t i = 0; i < 8; i++)
        {
            if (pseudo_random_value & (1 << i))    
            {
                gpio_high(SER);
            }
            else
            {
                gpio_low(SER);
            }

            gpio_high(SRCLK);
            gpio_low(SRCLK);

            gpio_high(RCLK);
            gpio_low(RCLK);

            // _delay_ms(1500);
            _delay_ms(100);
        }
    }

    return 0;
}
