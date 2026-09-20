/**
 * @author Maksym Palii
 * @brief 74hc595 Example 4 - different shift approaches
 * @date 2026 September 17
 */

// #define EXAMPLE_1        // Size: 246 bytes
// #define EXAMPLE_2        // Size: 314 bytes
// #define EXAMPLE_3        // Size: 314 bytes
// #define EXAMPLE_4        // Size: 224 bytes

#include <stdint.h>
#include "drivers/gpio.h"

void init_gpio(void);
void shift_byte(uint8_t);

int main(void)
{
    init_gpio();
    shift_byte(0b11001001);
    shift_byte(0b00000000);

    while(1)
    {

    }

    return 0;
}

void init_gpio(void)
{
    sbi_ddr(LED);
    sbi_ddr(SER);
    sbi_ddr(RCLK);
    sbi_ddr(SRCLK);
}

#ifdef EXAMPLE_1
    void shift_byte(uint8_t data)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            if (data & (1 << i))    
            {
                sbi_port(SER);
            }
            else
            {
                cbi_port(SER);
            }

            sbi_port(SRCLK);
            cbi_port(SRCLK);
        }

        sbi_port(RCLK);
        cbi_port(RCLK);
    }
#endif

#ifdef EXAMPLE_2
    void shift_byte(uint8_t data)
    {
        if (data & 0b00000001)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b00000010)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b00000100)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b00001000)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b00010000)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b00100000)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b01000000)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & 0b10000000)  sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        gpio_high(RCLK);
        gpio_low(RCLK);
    }
#endif

#ifdef EXAMPLE_3
    void shift_byte(uint8_t data)
    {
        if (data & (1 << 0))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 1))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 2))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 3))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 4))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 5))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 6))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        if (data & (1 << 7))    sbi_port(SER);
        else                    cbi_port(SER);
        sbi_port(SRCLK);
        cbi_port(SRCLK);

        gpio_high(RCLK);
        gpio_low(RCLK);
    }
#endif

#ifdef EXAMPLE_4
    void shift_byte(uint8_t data)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            if (data & 1U)
                sbi_port(SER);
            else
                cbi_port(SER);

            sbi_port(SRCLK);
            cbi_port(SRCLK);

            data >>= 1;
        }

        sbi_port(RCLK);
        cbi_port(RCLK);
    }
#endif
