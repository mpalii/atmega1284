#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include <stdint.h>

void init_seven_segment(void);
void seven_segment_split(uint16_t number);
void seven_segment_render(void);

#endif /* SEVEN_SEGMENT_H_ */
