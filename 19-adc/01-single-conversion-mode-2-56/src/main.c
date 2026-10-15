/**
 * @author Maksym Palii
 * @brief ADC - single conversion mode
 * @date 2026 October 01
 */

#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"
#include "drivers/adc.h"

int main(void)
{
    init_shift_register();
    init_seven_segment();
    init_adc();
    sbi_ddr(LED);

    while(1)
    {
        adc_start_conversion();

        // wait for conversion result
        while (!(ADCSRA & (_BV(ADIF))))
        {
            // profiling
            // sbi_pin(LED);
        }
        
        seven_segment_render(ADC);
        // profiling
        // sbi_pin(LED);
    }

    return 0;
}
