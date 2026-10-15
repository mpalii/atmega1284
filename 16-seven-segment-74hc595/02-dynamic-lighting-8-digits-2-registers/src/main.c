/**
 * @author Maksym Palii
 * @brief 8 digits 7-segment display with 74HC595, dynamic lighting
 * @date 2026 September 22
 */

#define F_CPU   8000000UL

#include <util/delay.h>
#include "drivers/shift_register.h"
#include "drivers/gpio.h"

static const uint8_t DIGIT_TO_MASK_TABLE[] = {
    0b00000011, // 0
    0b10011111, // 1
    0b00100101, // 2
    0b00001101, // 3
    0b10011001, // 4
    0b01001001, // 5
    0b01000001, // 6
    0b00011111, // 7
    0b00000001, // 8
    0b00001001, // 9
    0b00010001, // a
    0b11000001, // b
    0b01100011, // c
    0b10000101, // d
    0b01100001, // e
    0b01110001  // f
};

int main(void)
{
    init_shift_register();
    sbi_ddr(LED);
    
    while (1)
    {

        for (uint8_t i = 0; i < 8; i++)
        {
            uint8_t digit_position = (1 << i);
            for (uint8_t j = 0; j < 16; j++)
            {
                shift_byte(DIGIT_TO_MASK_TABLE[j]);
                shift_byte(digit_position);
                rclk_pulse();

                _delay_ms(500);
            }
        }
    }
    
    return 0;
}
