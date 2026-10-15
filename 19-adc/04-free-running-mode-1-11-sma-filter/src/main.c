/**
 * @author Maksym Palii
 * @brief ADC simple moving average (SMA filter)
 * @date 2026 October 03
 */

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"
#include "drivers/adc.h"

#define WINDOW_SIZE (4096)

uint16_t calculation_window_buffer[WINDOW_SIZE] = { 0, };
static volatile uint32_t buffer_sum = 0;
static volatile uint16_t index = 0;

ISR(ADC_vect)
{
    // profiling
    sbi_pin(LED);
    
    buffer_sum -= calculation_window_buffer[index];
    calculation_window_buffer[index] = ADC;
    buffer_sum += calculation_window_buffer[index];

    if (++index > (WINDOW_SIZE - 1))
    {
        index = 0;
    }
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
        uint32_t buffer_sum_copy;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            buffer_sum_copy = buffer_sum;
        }
        uint16_t filtered_result = (uint16_t) (buffer_sum_copy / WINDOW_SIZE);
        seven_segment_render(filtered_result);
    }

    return 0;
}

