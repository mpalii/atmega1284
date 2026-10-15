#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include <stdint.h>

void init_seven_segment(void);
void seven_segment_render_in_dec(uint16_t number);
void seven_segment_render_in_dec_no_loop(uint16_t number);
void seven_segment_render_in_dec_no_division(uint16_t number);
void seven_segment_render_in_hex(uint16_t number);
void seven_segment_render_in_hex_shift(uint16_t number);

#endif /* SEVEN_SEGMENT_H_ */
