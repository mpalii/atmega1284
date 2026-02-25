/**
 * @author Maksym Palii
 * @brief 74hc595 Example 2 - different shift approaches
 * @version 1.0
 * @date 2026-02-22
 */

#include <stdlib.h>
#include "drivers/gpio.h"

void init_gpio(void)
{
    sbi_ddr(_PA0);
    sbi_ddr(SER);
    sbi_ddr(RCLK);
    sbi_ddr(SRCLK);
}

// void shift_byte(uint8_t data)
// {
//     for (uint8_t i = 0; i < 8; i++)
//     {
//         if (data & (1 << i))    
//         {
//             sbi_port(SER);
//         }
//         else
//         {
//             cbi_port(SER);
//         }

//         sbi_port(SRCLK);
//         cbi_port(SRCLK);
//     }

//     sbi_port(RCLK);
//     cbi_port(RCLK);
// }

// Complie time optimization issue
// void shift_byte(uint8_t data)
// {
//     if (data & 0x00000001)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x00000010)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x00000100)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x00001000)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x00010000)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x00100000)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x01000000)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     if (data & 0x10000000)  sbi_port(SER);
//     else                    cbi_port(SER);
//     sbi_port(SRCLK);
//     cbi_port(SRCLK);

//     gpio_high(RCLK);
//     gpio_low(RCLK);
// }

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
