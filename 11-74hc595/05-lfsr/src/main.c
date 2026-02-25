/**
 * @author Maksym Palii
 * @brief 74hc595 Example 5 - linear-feedback shift register (LFSR)
 * @version 1.0
 * @date 2026-02-28
 * @example https://people.ece.cornell.edu/land/courses/ece4760/Math/GCC644/DDS/DDS_sine_noise_uart.c
 */

#define F_CPU   (8000000UL)
#define SEED    (17)

#define BIT_30  (0x40000000)    // 01000000 00000000 00000000 00000000
#define BIT_27  (0x08000000)    // 00001000 00000000 00000000 00000000

#include <stdbool.h>
#include <stdlib.h>
#include <util/delay.h>
#include "drivers/gpio.h"

int main(void)
{
    sbi_ddr(_PA0);

    gpio_set_output(SER);
    gpio_set_output(RCLK);
    gpio_set_output(SRCLK);

    uint32_t noise = 0xab5a55aa;   // some seed

    bool bit_0;
    bool bit_1;
    
    uint8_t increment;

    while(true)
    {        
        bit_0 = noise & BIT_27;
        bit_1 = noise & BIT_30;
        noise <<= 1;
        increment = bit_0 ^ bit_1;
        noise += increment;

        // shift data
        if (increment)    
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

        _delay_ms(70);
    }

    return 0;
}
