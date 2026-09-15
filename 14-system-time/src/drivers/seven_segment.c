/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 2.0
*/

#include "seven_segment.h"

#include "gpio.h"

#define DIGITS_NUMBER (4)
#define RADIX (10)

// Digits placed from lower to higher (1, 10, 100, 1000)
static const uint8_t DIGITS[DIGITS_NUMBER] = { DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1 };

static const uint8_t DIGIT_TO_MASK_TABLE[RADIX] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101, 0b01111101, 0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111	                        // 8, 9
};

static uint8_t buffer[DIGITS_NUMBER] = { };

static uint8_t current_digit = 0;

void seven_segment_split(uint16_t number)
{
    for (uint8_t i = 0; i < DIGITS_NUMBER; i++)
    {
        uint8_t extracted_digit = (uint8_t) (number % RADIX);
        buffer[i] = DIGIT_TO_MASK_TABLE[extracted_digit];
        number /= RADIX;
    }
}

void seven_segment_render(void) 
{
    if (current_digit >= DIGITS_NUMBER) 
    {
        current_digit = 0;
    }

    uint8_t mapped_number = buffer[current_digit];

    // Disable all segment and digit pins
    gpio_high(DIGIT_1);
    gpio_high(DIGIT_2);
    gpio_high(DIGIT_3);
    gpio_high(DIGIT_4);

    gpio_low(SEGMENT_a);
    gpio_low(SEGMENT_b);
    gpio_low(SEGMENT_c);
    gpio_low(SEGMENT_d);
    gpio_low(SEGMENT_e);
    gpio_low(SEGMENT_f);
    gpio_low(SEGMENT_g);
    gpio_low(SEGMENT_dp);

    // Enable appropriate segments
    if (mapped_number & 0x01) gpio_high(SEGMENT_a); 
    if (mapped_number & 0x02) gpio_high(SEGMENT_b); 
    if (mapped_number & 0x04) gpio_high(SEGMENT_c); 
    if (mapped_number & 0x08) gpio_high(SEGMENT_d); 
    if (mapped_number & 0x10) gpio_high(SEGMENT_e); 
    if (mapped_number & 0x20) gpio_high(SEGMENT_f); 
    if (mapped_number & 0x40) gpio_high(SEGMENT_g); 
    if (mapped_number & 0x80) gpio_high(SEGMENT_dp); 

    // Enable appropriate digit pin and increment index
    gpio_low(DIGITS[current_digit]);

    current_digit++;
}

void init_seven_segment(void)
{
    gpio_set_output(SEGMENT_a);
    gpio_set_output(SEGMENT_b);
    gpio_set_output(SEGMENT_c);
    gpio_set_output(SEGMENT_d);
    gpio_set_output(SEGMENT_e);
    gpio_set_output(SEGMENT_f);
    gpio_set_output(SEGMENT_g);
    gpio_set_output(SEGMENT_dp);

    gpio_set_output(DIGIT_1);
    gpio_set_output(DIGIT_2);
    gpio_set_output(DIGIT_3);
    gpio_set_output(DIGIT_4);

    seven_segment_split(0);
}