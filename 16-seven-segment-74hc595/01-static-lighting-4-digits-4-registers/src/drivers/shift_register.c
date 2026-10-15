#include "shift_register.h"

#include "gpio.h"

void init_shift_register(void)
{
    sbi_ddr(SER);
    sbi_ddr(RCLK);
    sbi_ddr(SRCLK);
}

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
}

void rclk_pulse(void)
{
    gpio_high(RCLK);
    gpio_low(RCLK);
}