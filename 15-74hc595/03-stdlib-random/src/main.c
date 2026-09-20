/**
 * @author Maksym Palii
 * @brief 74hc595 Example 3 - continuoss pseudo random output
 * @date 2026 September 17
 */

#define F_CPU   (8000000UL)
#define SEED    (17)

#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include "drivers/gpio.h"

int main(void)
{
    gpio_set_output(LED);

    gpio_set_output(SER);
    gpio_set_output(RCLK);
    gpio_set_output(SRCLK);

    srand(SEED);

    while(1)
    {
        uint8_t pseudo_random_value = (uint8_t) rand();

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

            _delay_ms(100);
        }

        _delay_ms(1500);
    }

    return 0;
}
