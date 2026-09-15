/**
 * @author Maksym Palii
 * @brief Task manager
 * @version 2.0
*/

#include "task_manager.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/atomic.h>

#include "drivers/seven_segment.h"

// Global time
static volatile uint32_t system_time_ms = 0;

// Task 1
#define T1 6U
static void task_1(void);
static volatile uint8_t time1;
static volatile bool task1_ready;

// Task 2
#define T2 1000U
static void task_2(void);
static volatile uint16_t time2;
static volatile bool task2_ready;

ISR (TIMER0_COMPA_vect)
{    
    // Increment global time
    system_time_ms++;

    // Task 1
    if (--time1 == 0)
    {
        task1_ready = true;
        time1 = T1;
    }

    // Task 2
    if (--time2 == 0)
    {
        task2_ready = true;
        time2 = T2;
    }
}

void init_tasks(void)
{
    time1 = T1;
    time2 = T2;

    task1_ready = false;
    task2_ready = false;
}

void handle_tasks(void) 
{
    bool task1;
    bool task2;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        task1 = task1_ready;
        task2 = task2_ready;

        task1_ready = false;
        task2_ready = false;
    }

    if (task1) task_1();
    if (task2) task_2();
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

static void task_1(void)
{
    seven_segment_render();
}

static void task_2(void)
{
    uint32_t time;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        time = system_time_ms;
    }
    // Display elapsed time in seconds
    seven_segment_split((uint16_t)(time / 1000));
}