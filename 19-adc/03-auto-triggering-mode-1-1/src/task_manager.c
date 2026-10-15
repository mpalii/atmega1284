/**
 * @author Maksym Palii
 * @brief Task manager
 * @version 2.0
*/

#include "task_manager.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/atomic.h>

#include "drivers/adc.h"
#include "drivers/seven_segment.h"

// Task 1
#define T1 1U
static void task_1(void);
static volatile uint8_t time1;
static volatile bool task1_ready;

ISR (TIMER0_COMPA_vect)
{    
    // Task 1
    if (--time1 == 0)
    {
        task1_ready = true;
        time1 = T1;
    }
}

void init_tasks(void)
{
    time1 = T1;

    task1_ready = false;
}

void handle_tasks(void) 
{
    bool task1;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        task1 = task1_ready;

        task1_ready = false;
    }

    if (task1) task_1();
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

static void task_1(void)
{
    uint16_t conversion_result = adc_get_conversion_result();
    seven_segment_render(conversion_result);
}
