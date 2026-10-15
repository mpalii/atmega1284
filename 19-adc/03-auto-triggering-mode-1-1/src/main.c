/**
 * @author Maksym Palii
 * @brief ADC - auto trigger mode
 * @date 2026 October 03
 */

#include <avr/interrupt.h>

#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"
#include "drivers/timer0.h"
#include "drivers/adc.h"
#include "task_manager.h"

int main(void)
{
    init_shift_register();
    init_seven_segment();
    init_timer0();
    init_adc();
    init_tasks();
    adc_start_conversion();

    sei();
    sbi_ddr(LED);
	
    while (1)
    {
        handle_tasks();
    }

    return 0;
}