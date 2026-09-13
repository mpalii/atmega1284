/**
 * @author Maksym Palii
 * @brief Advanced fuses configuration
 * @date 2026 September 13
 */

#define F_CPU (1000000UL)

#include <util/delay.h>
#include "drivers/gpio.h"

int main(void)
{
    gpio_set_output(_PA0);

    while(1)
    {
        sbi_pin(_PA0);
        _delay_ms(1000);
    }

    return 0;
}
