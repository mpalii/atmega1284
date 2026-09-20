/**
 * @author Maksym Palii
 * @brief 74hc595 Example 6 - linear-feedback shift register (LFSR)
 * @date 2026 September 20
 * @example https://people.ece.cornell.edu/land/courses/ece4760/Math/GCC644/DDS/DDS_sine_noise_uart.c
 */

#define F_CPU   (8000000UL)
#define BIT_30  (UINT32_C(1) << 30)     // 01000000 00000000 00000000 00000000
#define BIT_27  (UINT32_C(1) << 27)     // 00001000 00000000 00000000 00000000

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "drivers/gpio.h"
#include "drivers/shift_register.h"

/*
 * Test selector section
 */
#define EXAMPLE_1
// #define EXAMPLE_2

int main(void)
{
    init_shift_register();
    sbi_ddr(LED);

    uint32_t accumulator = 0xab5a55aa;

    while (true)
    {
        accumulator <<= 1;
        bool bit_27 = (accumulator & BIT_27) != 0;
        bool bit_30 = (accumulator & BIT_30) != 0;
        bool feedback = bit_27 ^ bit_30;
        accumulator += feedback;

        #ifdef EXAMPLE_1
            shift_byte((uint8_t) accumulator);
            rclk_pulse();
            _delay_ms(1000);
        #endif

        #ifdef EXAMPLE_2
            shift_bit(feedback);
            rclk_pulse();
            _delay_ms(70);
        #endif
    }

    return 0;
}
