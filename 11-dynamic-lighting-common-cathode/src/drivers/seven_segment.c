/**
 * @author Maksym Palii
 * @brief Seven-segment display with common cathode driver (4 digits) 
 * @version 1.0
*/

#include <stdint.h>
#include "gpio.h"

// Digits placed from lower to higher (1, 10, 100, 1000)
static const uint8_t DIGITS[] = { DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1 };

static const uint8_t SEGMENT_PATTERNS[] = {
    0b00111111,     // 0
    0b00000110,     // 1
    0b01011011,	    // 2
    0b01001111,	    // 3
    0b01100110,     // 4
    0b01101101,	    // 5
    0b01111101,	    // 6
    0b00000111,	    // 7
    0b01111111,     // 8
    0b01101111      // 9
};

static uint8_t current_digit_index;

void seven_segment_init(void)
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

    current_digit_index = 0;
}

void seven_segment_render(uint16_t number) 
{
    // Check index out of bound
    if (current_digit_index >= sizeof(DIGITS) / sizeof(DIGITS[0])) 
	{
		current_digit_index = 0;
	}

    // Extract digit to render
	for (uint8_t i = 0; i < current_digit_index; i++)
	{
		number /= 10;
	}

    uint8_t mapped_number = SEGMENT_PATTERNS[number % 10];

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
    gpio_low(DIGITS[current_digit_index]);
    current_digit_index++;
}
