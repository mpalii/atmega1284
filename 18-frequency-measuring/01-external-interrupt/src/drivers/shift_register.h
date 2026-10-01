#ifndef SHIFT_REGISTER
#define SHIFT_REGISTER

#include <stdbool.h>
#include <stdint.h>

void init_shift_register(void);
void shift_byte(uint8_t data);
void rclk_pulse(void);

#endif /* SHIFT_REGISTER */