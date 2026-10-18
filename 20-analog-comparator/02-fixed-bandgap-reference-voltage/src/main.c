/**
 * @author Maksym Palii
 * @brief Analog Comparator - bandgap reference
 * @date 2026 October 18
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

    // Analog Comparator Bandgap Select
    // Replace the positive pin AIN0
    ACSR |= _BV(ACBG);

    while (1)
    {
        // When the fixed bandgap reference voltage (1.1 V) is higher than the voltage on the negative pin AIN1
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