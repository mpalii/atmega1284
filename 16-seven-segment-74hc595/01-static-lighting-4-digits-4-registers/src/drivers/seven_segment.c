/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 2.0
*/

#include "seven_segment.h"

#include "gpio.h"
#include "shift_register.h"

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

void init_seven_segment(void)
{
    shift_byte(0xFF);
    shift_byte(0xFF);
    shift_byte(0xFF);
    shift_byte(0xFF);
    rclk_pulse();
}

void seven_segment_render_in_dec(uint16_t number)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t extracted_digit = (uint8_t) (number % 10);
        uint8_t mask = DIGIT_TO_MASK_TABLE[extracted_digit];
        shift_byte(mask);
        number /= 10;
    }

    rclk_pulse();
}

void seven_segment_render_in_dec_no_loop(uint16_t number)
{
    uint8_t extracted_digit = (uint8_t) (number % 10);
    uint8_t mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number /= 10;

    extracted_digit = (uint8_t) (number % 10);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number /= 10;

    extracted_digit = (uint8_t) (number % 10);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number /= 10;

    extracted_digit = (uint8_t) (number % 10);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);

    rclk_pulse();
}

void seven_segment_render_in_dec_no_division(uint16_t number)
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

    uint8_t digit_3 = 0;
    while (number >= 100)
    {
        number -= 100;
        ++digit_3;
    }

    uint8_t digit_2 = 0;
    while (number >= 10)
    {
        number -= 10;
        ++digit_2;
    }

    shift_byte(DIGIT_TO_MASK_TABLE[number]);
    shift_byte(DIGIT_TO_MASK_TABLE[digit_2]);
    shift_byte(DIGIT_TO_MASK_TABLE[digit_3]);
    shift_byte(DIGIT_TO_MASK_TABLE[digit_4]);

    rclk_pulse();
}

void seven_segment_render_in_hex(uint16_t number)
{
    uint8_t extracted_digit = (uint8_t) (number % 16);
    uint8_t mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number /= 16;

    extracted_digit = (uint8_t) (number % 16);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number /= 16;

    extracted_digit = (uint8_t) (number % 16);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number /= 16;

    extracted_digit = (uint8_t) (number % 16);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);

    rclk_pulse();
}

void seven_segment_render_in_hex_shift(uint16_t number)
{
    uint8_t extracted_digit = (uint8_t) (number & 0x0F);
    uint8_t mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number >>= 4;

    extracted_digit = (uint8_t) (number & 0x0F);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number >>= 4;

    extracted_digit = (uint8_t) (number & 0x0F);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);
    number >>= 4;

    extracted_digit = (uint8_t) (number & 0x0F);
    mask = DIGIT_TO_MASK_TABLE[extracted_digit];
    shift_byte(mask);

    rclk_pulse();
}