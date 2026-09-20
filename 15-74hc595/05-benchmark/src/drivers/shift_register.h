#ifndef SHIFT_REGISTER
#define SHIFT_REGISTER

#include <stdint.h>

void init_shift_register(void);
void shift(uint8_t);
void shift_with_masks(uint8_t);
void shift_with_shift(uint8_t);
void shift_uint16(uint16_t);
void shift_with_shift_uint16(uint16_t);
void shift_byte(uint8_t data);
void rclk_pulse(void);

#endif /* SHIFT_REGISTER */