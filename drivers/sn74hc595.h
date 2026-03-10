#ifndef SN74HC595_H_
#define SN74HC595_H_

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

void sn74hc595_init(void)
{
    sbi_ddr(SER);
    sbi_ddr(RCLK);
    sbi_ddr(SRCLK);
}

void sn74hc595_shift(uint8_t data)
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

#endif /* SN74HC595_H_ */