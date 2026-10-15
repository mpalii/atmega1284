/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 2.0
*/

#include "seven_segment.h"

#include "shift_register.h"

#define DECIMAL_POINT_BIT   (7)
#define DIGITS_NUMBER       (4)
#define EMPTY_MASK          (0)
#define RADIX               (10)

static const uint8_t DIGIT_TO_MASK_TABLE[RADIX] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101, 0b01111101, 0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111	                        // 8, 9
};

static uint8_t buffer[DIGITS_NUMBER] = { };

static uint8_t current_digit = 0;

void seven_segment_split(uint16_t number)
{
    // trim number
    while (number > 9999)
    {
        number -= 10000;
    }

    uint8_t digit_4 = 0;
    while (number >= 1000)
    {
        number -= 1000;
        ++digit_4;
    }
    buffer[3] = DIGIT_TO_MASK_TABLE[digit_4];

    uint8_t digit_3 = 0;
    while (number >= 100)
    {
        number -= 100;
        ++digit_3;
    }
    buffer[2] = DIGIT_TO_MASK_TABLE[digit_3];

    uint8_t digit_2 = 0;
    while (number >= 10)
    {
        number -= 10;
        ++digit_2;
    }
    buffer[1] = DIGIT_TO_MASK_TABLE[digit_2] | (1 << DECIMAL_POINT_BIT);

    buffer[0] = DIGIT_TO_MASK_TABLE[number];
}

void seven_segment_render(void) 
{
    if (current_digit >= DIGITS_NUMBER) 
    {
        current_digit = 0;
    }

    shift_byte((uint8_t) (~(1 << current_digit)));
    shift_byte(buffer[current_digit]);
    rclk_pulse();

    current_digit++;
}

void init_seven_segment(void)
{
    shift_byte(0xFF);
    shift_byte(0xFF);
    rclk_pulse();

    seven_segment_split(0);
}