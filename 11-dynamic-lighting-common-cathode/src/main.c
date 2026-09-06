/**
 * @author Maksym Palii
 * @brief Dynamic lighting, 4-digits seven-segment display with common cathode
 * @date 2026 September 06
 */

#define F_CPU 8000000UL
#define FAST_DELAY  5
#define SLOW_DELAY  50
#define DELAY       SLOW_DELAY

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/seven_segment.h"


int main(void)
{
    seven_segment_init();

    while (true)
    {
        seven_segment_render(1234);
        _delay_ms(DELAY);
    }
}
