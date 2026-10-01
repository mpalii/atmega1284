/**
 * @author Maksym Palii
 * @brief Frequency meter, external interrupt based approach
 * @date 2026 September 23
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/atomic.h>

#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"

void init_tasks(void);
void init_timer_0(void);
void init_timer_1(void);
void init_timer_2(void);
void init_external_interrupt_0(void);

// Timer/Counter 1 overflow counter
volatile uint8_t TCNT1_overflow_counter = 0;

// Timer/Counter 1 value
volatile uint32_t period_ticks = 0;

// Task 1
#define T1 250
void task_1(void);
volatile uint8_t time1;
volatile bool task1_ready;

ISR(TIMER0_COMPA_vect)
{    
    // Task 1
    if (--time1 == 0)
    {
        task1_ready = true;
        time1 = T1;
    }
}

ISR(INT0_vect)
{
    uint16_t TCNT1_copy = TCNT1;
    TCNT1 = 0;

    uint8_t TCNT1_overflow_counter_copy = TCNT1_overflow_counter;
    TCNT1_overflow_counter = 0;

    period_ticks = (((uint32_t) TCNT1_overflow_counter_copy) << 16) | TCNT1_copy;
}

ISR(TIMER1_OVF_vect)
{
    TCNT1_overflow_counter++;
}

int main(void)
{
    init_shift_register();
    init_seven_segment();
    init_tasks();
    init_timer_0();
    init_timer_1();
    init_timer_2();
    init_external_interrupt_0();
    gpio_set_output(LED);
    sei();
	
    while (true)
    {
        if (task1_ready)
        {
            task1_ready = false;
            task_1();
        }
    }
}

void init_tasks(void)
{    
    time1 = T1;

    task1_ready = false;
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
void init_timer_0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	124;                     //Sset the compare reg to 125 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00);  // clk/64 (From prescaler)
}

/****************************************************************************/
/* Set up timer 1 without prescaler                                         */
/****************************************************************************/
void init_timer_1(void)
{
    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(CS10);     // clk I/O/1 (No prescaling)
	
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(TOIE1);    // Timer/Counter1, Overflow Interrupt Enable
}

/*******************************************************************************/
/* Set up timer 2 for toggling OC2A on Compare Match - PD7                     */
/*******************************************************************************/
void init_timer_2(void)
{
    // make OC2A output
    gpio_set_output(OC2A);

    // TCCR2A – Timer/Counter2 Control Register channel A 
    TCCR2A = _BV(COM2A0) | _BV(WGM21);  // Toggle OC2A on Compare Match + CTC

    // TCCR2B – Timer/Counter2 Control Register channel B
    TCCR2B = _BV(CS21) | _BV(CS20);     // clk/32 (From prescaler) - 8000 ticks
    // TCCR2B = _BV(CS21);                 // clk/8 (From prescaler) - 2000 ticks

    // OCR2A – Timer/Counter2 Output Compare Register channel A
    OCR2A = 124;                        // zero based
}

void init_external_interrupt_0(void)
{
    // The falling edge of INT0 generates an interrupt request
    EICRA = _BV(ISC01);

    // External Interrupt Request 0 Enable
    EIMSK = _BV(INT0);
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

void task_1(void)
{
    uint32_t period_ticks_copy;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        period_ticks_copy = period_ticks;
    }

    // Render frequency
    if (period_ticks_copy != 0)
    {
        // seven_segment_render((uint16_t) (F_CPU / period_ticks_copy));
        seven_segment_render((uint16_t) period_ticks_copy);
    }
}
