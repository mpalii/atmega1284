//Run two timers in the next modes:
// timer 0 -- compare-match timebase (system timer)
// timer 1 -- input capture from analog comparator

// task 1 will  print the periods 
// timer0 compare ISR will increment a timer
// timer1 capture ISR will compute a period from the capture

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

// Task 1
#define T1 250
void task_1(void);
volatile uint8_t time1;
volatile bool task1_ready;

// timer 1 capture variables for computing sq wave period	
volatile unsigned int currentT1capture, previousT1capture, period_ticks; 
         
ISR (TIMER0_COMPA_vect) 
{    
    // Task 1
    if (--time1 == 0)
    {
        task1_ready = true;
        time1 = T1;
    }
}

ISR (TIMER1_CAPT_vect)
{
    // read timer1 input capture register
    currentT1capture = ICR1 ; 
    // compute time between captures
    period_ticks =  currentT1capture - previousT1capture;
    previousT1capture = currentT1capture ;
}

//**********************************************************       
//Entry point and task scheduler loop
int main(void)
{  
    init_shift_register();
    init_seven_segment();
    init_tasks();
    init_timer_0();
    init_timer_1();
    init_timer_2();
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
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00);  // clk/64 (From prescaler)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	124;                     //set the compare reg to 125 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

/****************************************************************************/
/* Set up timer 1 for Input Capture mode                                    */
/* Capture rising edge, no prescaling, interrupt based                      */
/****************************************************************************/
void init_timer_1(void)
{   
    //  TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(ICES1) | _BV(CS10); // set capture to positive edge, full counting rate

    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(ICIE1) ;            // Timer/Counter1 Input Capture Interrupt Enable
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
        seven_segment_render((uint16_t) (F_CPU / period_ticks_copy));
        // seven_segment_render((uint16_t) period_ticks_copy);
    }
}
 