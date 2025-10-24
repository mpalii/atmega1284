/**
 * @author Maksym Palii
 * @brief Seven-segment display with common cathode driver (4 digits) 
 * @version 1.0
*/

#include "cc56.h"
#include "gpio.h"

// Digits placed from lower to higher
const uint8_t DIGITS[] = { DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1 };

const uint8_t NUMBERS[] = {
    0b00111111, 0b00000110, 0b01011011,	0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101,	0b01111101,	0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111,	0b01110111,	0b01111100,	// 8, 9, A, B
    0b00111001,	0b01011110,	0b01111001, 0b01110001	// C, D, E, F
};

uint8_t current_digit = 0;

void cc56_init(void)
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
}

void cc56_render(uint16_t number) 
{
    gpio_low(SEGMENT_a);
    gpio_low(SEGMENT_b);
    gpio_low(SEGMENT_c);
    gpio_low(SEGMENT_d);
    gpio_low(SEGMENT_e);
    gpio_low(SEGMENT_f);
    gpio_low(SEGMENT_g);
    gpio_low(SEGMENT_dp);
    
    gpio_high(DIGIT_1);
    gpio_high(DIGIT_2);
    gpio_high(DIGIT_3);
    gpio_high(DIGIT_4);

    if (current_digit >= sizeof(DIGITS)) 
	{
		current_digit = 0;
	}

	for (int i = 0; i < current_digit; i++)
	{
		number /= 10;
	}
	
	number %= 10;


    uint8_t mapped_number = NUMBERS[number];

    if (mapped_number & 0x01) gpio_high(SEGMENT_a); 
    if (mapped_number & 0x02) gpio_high(SEGMENT_b); 
    if (mapped_number & 0x04) gpio_high(SEGMENT_c); 
    if (mapped_number & 0x08) gpio_high(SEGMENT_d); 
    if (mapped_number & 0x10) gpio_high(SEGMENT_e); 
    if (mapped_number & 0x20) gpio_high(SEGMENT_f); 
    if (mapped_number & 0x40) gpio_high(SEGMENT_g); 
    if (mapped_number & 0x80) gpio_high(SEGMENT_dp); 

    gpio_low(DIGITS[current_digit]);

    current_digit++;
}
