#include "shift_register.h"

#include "gpio.h"

#if (!defined(SER))
# error "SN74HC595 - serial data line SER must be specified!"
#endif

#if (!defined(SRCLK))
# error "SN74HC595 - serial clock line SRCLK must be specified!"
#endif

#if (!defined(RCLK))
# error "SN74HC595 - register clock line RCLK must be specified!"
#endif

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