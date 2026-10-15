/**
 * @author Maksym Palii
 * @brief ADC - free running mode
 * @date 2026 October 01
 */

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"
#include "drivers/adc.h"

volatile uint16_t conversion_result = 0;

ISR(ADC_vect)
{
    // profiling
    sbi_pin(LED);
    conversion_result = ADC;
}

int main(void)
{
    init_shift_register();
    init_seven_segment();
    init_adc();
    sbi_ddr(LED);

    sei();
    adc_start_conversion();

    while(1)
    {
        uint16_t conversion_result_copy;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            conversion_result_copy = conversion_result;
        }
        seven_segment_render(conversion_result_copy);
    }

    return 0;
}
