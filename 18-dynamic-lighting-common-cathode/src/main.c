/**
 * @author Maksym Palii
 * @brief Dynamic lighting, 4-digits seven-segment display with common cathode
 * @version 1.0
 * @date 2025 October 24
 */

#define F_CPU 8000000UL

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/cc56.h"
#include "drivers/gpio.h"

int main(void)
{
    cc56_init();

    while (true)
    {
        cc56_render(2025);
        _delay_ms(5);
    }
}
