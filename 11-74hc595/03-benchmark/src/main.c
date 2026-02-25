/**
 * @author Maksym Palii
 * @brief 74hc595 Example 3 - benchmarking with Timer/Counter 0
 * @version 1.0
 * @date 2026-02-22
 */

#include <stdlib.h>
#include "drivers/gpio.h"

void init_gpio(void)
{
    sbi_ddr(SER);
    sbi_ddr(RCLK);
    sbi_ddr(SRCLK);
}

void shift_byte_for_loop(uint8_t data)
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

void shift_byte_with_masks(uint8_t data)
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

void benchmark_test_1(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    // No actions           // 0

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_for_loop(0x00);
    shift_byte_for_loop(time);
}

void benchmark_test_2(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    sbi_ddr(_PA0);          // 2

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_for_loop(0x00);
    shift_byte_for_loop(time);
}

void benchmark_test_3(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    __asm__("nop");         // 1

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_for_loop(0x00);
    shift_byte_for_loop(time);
}

void benchmark_test_4(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    __asm__ (
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
    );                      // 5

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_for_loop(0x00);
    shift_byte_for_loop(time);
}

void benchmark_for_loop_0x00(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    shift_byte_for_loop(0x00);  // 64 + 16 + 2 +1 = 83

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_for_loop(time);
}

void benchmark_for_loop_0xFF(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    shift_byte_for_loop(0xFF);  // 32 + 16 + 8 + 2 +1 = 59

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_for_loop(time);
}

void benchmark_with_masks_0x00(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    shift_byte_with_masks(0x00);  // 64 + 32 + 4 +1 = 101

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_with_masks(time);
}

void benchmark_with_masks_0xFF(void)
{
    init_gpio();

    TCCR0B = _BV(CS00);     // Launch Timer/Counter0 without prescaling

    shift_byte_with_masks(0xFF);  // 64 + 8 + 4 + 1 = 77

    uint8_t time = TCNT0;   
    TCCR0B = 0x00;          // Stop Timer/Counter0

    shift_byte_with_masks(time);
}

int main(void)
{
    benchmark_test_1();                 // 0
    // benchmark_test_2();                 // 2
    // benchmark_test_3();                 // 1
    // benchmark_test_4();                 // 5

    // benchmark_for_loop_0x00();          // 83
    // benchmark_for_loop_0xFF();          // 59

    // benchmark_with_masks_0x00();        // 101
    // benchmark_with_masks_0xFF();        // 77

    while(1)
    {

    }

    return 0;
}
