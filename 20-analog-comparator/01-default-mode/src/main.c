/**
 * @author Maksym Palii
 * @brief Analog Comparator
 * @date 2026 October 17
 */

#define F_CPU   (8000000UL)

#include <avr/io.h>
#include <util/delay.h>

#include "drivers/gpio.h"

int main(void)
{	
    gpio_set_output(LED);

    // blink 8/2 times
    for (int8_t i = 0; i < 8; i++)
    {
        sbi_pin(LED);
        _delay_ms(250);
    }

    // Disable analog comparator
    // ACSR |= _BV(ACD);

    while (1)
    {
        // When the voltage on the positive pin AIN0 is higher than the voltage on the negative pin AIN1
        if (bit_is_set(ACSR, ACO))
        {
            gpio_low(LED);
        }
        else
        {
            gpio_high(LED);
        }
    }

    return 0;
}