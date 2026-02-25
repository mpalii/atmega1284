/**
 * @author Maksym Palii
 * @brief Shift-register SN74HC595 driver 
 * @version 1.0
*/

#include "sn74hc595.h"
#include "gpio.h"

void shift_byte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & (1 << i))    
            sbi_port(SER);
        else                    
            cbi_port(SER);

        sbi_port(SRCLK);
        cbi_port(SRCLK);
    }
}

void shift_uint16(uint16_t data)
{
    shift_byte((uint8_t)(data & 0xFF));
    shift_byte((uint8_t)(data >> 8));
    
    sbi_port(RCLK);
    cbi_port(RCLK);
}

// void shift_uint16(uint16_t data)
// {
//     for (uint8_t i = 0; i < 16; i++)
//     {
//         if (data & (1 << i))    
//             sbi_port(SER);
//         else                    
//             cbi_port(SER);

//         sbi_port(SRCLK);
//         cbi_port(SRCLK);
//     }

//     sbi_port(RCLK);
//     cbi_port(RCLK);
// }

void init_sn74hc595(void)
{
    // indicator
    gpio_set_output(LED);

    gpio_set_output(SER);
    gpio_set_output(RCLK);
    gpio_set_output(SRCLK);
}