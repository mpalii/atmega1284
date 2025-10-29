/**
 * @author Maksym Palii
 * @brief External interrupts, interrupts priority
 * @version 1.0
 * @date 2025 October 29
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

ISR(INT0_vect)
{       
    // blink 2 times
    for(int i = 0; i < 2; i++) 
    {
        gpio_high(LED_INT0);
        _delay_ms(250);
        gpio_low(LED_INT0);
        _delay_ms(250);
    }
}

ISR(INT1_vect)
{       
    // blink 2 times
    for(int i = 0; i < 2; i++) 
    {
        gpio_high(LED_INT1);
        _delay_ms(250);
        gpio_low(LED_INT1);
        _delay_ms(250);
    }
}

ISR(INT2_vect)
{       
    // blink 2 times
    for(int i = 0; i < 2; i++) 
    {
        gpio_high(LED_INT2);
        _delay_ms(250);
        gpio_low(LED_INT2);
        _delay_ms(250);
    }
}

ISR(TIMER1_OVF_vect)
{
    // Nested interrupts
    // sei();

    // blink 4 times
    for(int i = 0; i < 4; i++) 
    {
        gpio_low(LED_TIMER1);
        _delay_ms(250);
        gpio_high(LED_TIMER1);
        _delay_ms(250);
    }
}

/****************************************************************************/
/* Set up timer 1 for 8.388608 Sec timebase (with overflow)                 */
/* (1024 (prescaler) * 2^16 (65536)) / 8_000_000 MHz = 8.388608Sec          */
/****************************************************************************/
void init_timer_1(void)
{
    // TCCR1B – Timer/Counter1 Control Register channel B
    TCCR1B = _BV(CS12) | _BV(CS10);  // CTC mode and clk/1024 (From prescaler)
	
    // TIMSK1 – Timer/Counter1 Interrupt Mask Register
    TIMSK1 = _BV(TOIE1);            // Timer/Counter1, Overflow Interrupt Enable
}

int main(void)
{
    // Enable pull-up resistors
    gpio_high(INT0_PIN);
    gpio_high(INT1_PIN);
    gpio_high(INT2_PIN);

    // Configure LEDs
    gpio_high(LED_TIMER1);
    gpio_set_output(LED_TIMER1);
    gpio_set_output(LED_INT0);
    gpio_set_output(LED_INT1);
    gpio_set_output(LED_INT2);

    // Configure external interrupts
    EICRA |= _BV(ISC21) | _BV(ISC11) | _BV(ISC01);
    EIMSK |= _BV(INT2) |  _BV(INT1) | _BV(INT0);

    // Timer 1
    init_timer_1();

    // Enable global interrupts
    sei();
	
    while (true)
    {
        // NOP
    }
}
