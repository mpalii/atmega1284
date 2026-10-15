/**
 * @author Maksym Palii
 * @brief System time to 4 digits 7-segment display
 * @date 2026 October 04
 */

#include <avr/interrupt.h>
#include <stdbool.h>

#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"
#include "drivers/timer0.h"
#include "task_manager.h"

int main(void)
{
    init_shift_register();
    init_seven_segment();
    init_tasks();
    init_timer0();
    sei();
	
    while (true)
    {
        handle_tasks();
    }
}