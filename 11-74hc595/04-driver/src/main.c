/**
 * @author Maksym Palii
 * @brief 74hc595 Example 4 - driver based approach
 * @version 1.0
 * @date 2026-02-25
 */

#define F_CPU (8000000UL)

#include <util/delay.h>
#include "drivers/sn74hc595.h"

int main(void)
{
    init_sn74hc595();

    uint16_t counter = 0;

    while(1)
    {
        shift_uint16(counter);
        counter++;
        _delay_ms(100);    
    }

    return 0;
}
