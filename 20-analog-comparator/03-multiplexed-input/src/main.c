/**
 * @author Maksym Palii
 * @brief Analog Comparator - multiplexed input
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

    // Analog Comparator Multiplexer Enable
    ADCSRB |= _BV(ACME);
    // Analog Channel Selection - ADC3 channel
    ADMUX |= _BV(MUX1) | _BV(MUX0);    

    while (1)
    {
        // When the voltage on the positive pin AIN0 is higher than the voltage on ADC multiplexed channel
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