/**
 * @author Maksym Palii
 * @brief 74hc595 Example 1 - continuous incremental output
 * @date 2026 September 17
 */

#define F_CPU   (8000000UL)

#include <stdlib.h>
#include <util/delay.h>
#include "drivers/gpio.h"

static inline void init_gpio(void);
static inline void shift_byte(uint8_t);

int main(void)
{
    init_gpio();

    uint8_t counter = 0;
    while(1)
    {
        shift_byte(counter++);
        _delay_ms(1000);
    }

    return 0;
}

static inline void init_gpio(void)
{
    gpio_set_output(LED);
    gpio_set_output(SER);
    gpio_set_output(RCLK);
    gpio_set_output(SRCLK);
}

static inline void shift_byte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & (1 << i))    
        {
            gpio_high(SER);
        }
        else
        {
            gpio_low(SER);
        }

        gpio_high(SRCLK);
        gpio_low(SRCLK);
    }

    gpio_high(RCLK);
    gpio_low(RCLK);
}
