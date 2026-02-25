#ifndef SN74HC595_H_
#define SN74HC595_H_

#include <stdint.h>

void init_sn74hc595(void);
void shift_uint16(uint16_t data);

#endif /* SN74HC595_H_ */