/**
 * @author Maksym Palii
 * @brief Multitasking, example of asynchronous execution using simpliest round robin scheduler
 * @date 2026 September 06
 *
 * - PA0 - scheduler indicator (system tick is 1mSec so 500Hz is expected frequency)
 * - task 1 - 2Hz frequency beacon flasher - PD0
 * - task 2 - 500Hz frequency beacon flasher - PD1
 * - task 3 - 25/50Hz frequency beacon flasher - PD2
 * - task 4 - 0.5Hz frequency beacon flasher - PD3
 * - task 5 - button handler, enable or disable double speed flashing frequency in task 3 - PB0
 * - task 6 (HARDWARE)- 4MHz squarewave generator - PD4
 *
 * Notes:
 * IT IS IMPORTANT! All frequencies of flashers with this approach are approximations
 * WE ONLY CAN STATE that all tasks will be executed within the one period of our scheduler (1mSec)
 */

#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

void init_io_pins(void);
void init_tasks(void);
void init_timer_0(void);
void init_timer_1(void);

// Task 1
#define T1 250
void task_1(void);
volatile uint8_t time1;
volatile bool task1_ready;

// Task 2
#define T2 1
void task_2(void);
volatile uint8_t time2;
volatile bool task2_ready;

// Task 3
#define T3 20
void task_3(void);
volatile uint8_t time3;
volatile bool task3_ready;

// Task 4
#define T4 1000U
void task_4(void);
volatile uint16_t time4;
volatile bool task4_ready;

// Task 5
#define T5 15
void task_5(void);
volatile uint8_t time5;
volatile bool task5_ready;

bool button_was_pressed = false;
volatile bool double_speed_enabled = false;

ISR(TIMER0_COMPA_vect)
{
    // Toggle pin 0 port A
    PINA |= _BV(PINA0);

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

    // Task 3
    if (--time3 == 0)
    {
        task3_ready = true;
        time3 = double_speed_enabled ? (T3 / 2) : T3;
    }

    // Task 4
    if (--time4 == 0)
    {
        task4_ready = true;
        time4 = T4;
    }

    // Task 5
    if (--time5 == 0)
    {
        task5_ready = true;
        time5 = T5;
    }
}

int main(void)
{
    init_io_pins();
    init_tasks();
    init_timer_0();
    init_timer_1();

    sei();

    while (true)
    {
        if (task1_ready)
        {
            task1_ready = false;
            task_1();
        }

        if (task2_ready)
        {
            task2_ready = false;
            task_2();
        }

        if (task3_ready)
        {
            task3_ready = false;
            task_3();
        }

        if (task4_ready)
        {
            task4_ready = false;
            task_4();
        }

        if (task5_ready)
        {
            task5_ready = false;
            task_5();
        }
    }
}

void init_io_pins(void)
{
    // Set port A pin 0 as output
    DDRA |= _BV(DDRA0);

    // Set port A pin 0 driven HIGH
    PORTA |= _BV(PORTA0);

    // Enable internal pull-up resistor pin 0 (port B)
    PORTB |= _BV(PORTB0);

    // Set port D pin 0, 1, 2, 3 and 4 as output
    DDRD |= 0 
            | _BV(DDRD0) 
            | _BV(DDRD1) 
            | _BV(DDRD2) 
            | _BV(DDRD3) 
            | _BV(DDRD4);
}

void init_tasks(void)
{
    time1 = T1;
    time2 = T2;
    time3 = T3;
    time4 = T4;
    time5 = T5;

    task1_ready = false;
    task2_ready = false;
    task3_ready = false;
    task4_ready = false;
    task5_ready = false;
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/

void init_timer_0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);

    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00);

    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A = 124;

    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

void task_1(void)
{
    PIND |= _BV(PIND0);
}

void task_2(void)
{
    PIND |= _BV(PIND1);
}

void task_3(void)
{
    PIND |= _BV(PIND2);
}

void task_4(void)
{
    PIND |= _BV(PIND3);
}

void task_5(void)
{
    // Check whether button was pressed
    if (bit_is_clear(PINB, PINB0) && !button_was_pressed)
    {
        button_was_pressed = true;

        // Button push handling
        double_speed_enabled = !double_speed_enabled;
    }

    // Check whether button was released
    if (bit_is_set(PINB, PINB0) && button_was_pressed)
    {
        button_was_pressed = false;

        // Button release handling
        /* NOP */
    }
}

/*******************************************************************************/
/* Set up timer 1 for toggling OC1B on Compare Match - PD4                     */
/* (1 (prescaler) * 1 (OCR0B + 1)) / 8_000_000 MHz = 0.000000125Sec = 125nSec  */
/*******************************************************************************/

void init_timer_1(void)
{
    // TCCR1A – Timer/Counter1 Control Register channel A
    TCCR1A = _BV(COM1B0);

    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(WGM12) | _BV(CS10);

    // OCR1A – Timer/Counter1 Output Compare Register channel A
    OCR1A = 0;
}
