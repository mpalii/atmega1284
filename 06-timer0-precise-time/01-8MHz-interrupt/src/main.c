/**
 * @author Maksym Palii
 * @brief Timer 0 usage example, 25kHz generator, 8MHz frequency
 * @version 1.0
 * @date 2026 January 25
 */

#include <avr/interrupt.h>
#include <avr/io.h>

void init_io_pins(void);
void init_timer_0(void);

int main(void)
{
    init_io_pins();
    init_timer_0();
    sei();

    while (1) 
    { 
        // NOP
    }
}

void init_io_pins(void)
{
    // Set port A pin 0 as output
    DDRA |= _BV(DDRA0);
}

/****************************************************************************/
/* Set up timer 0 for 20 uSec timebase                                      */
/* (1 (prescaler) * 160 (OCR0A + 1)) / 8_000_000 MHz = 0.00002Sec = 20uSec  */
/****************************************************************************/
void init_timer_0(void)
{	
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);    // Clear Timer on Compare Match (CTC) mode (only works with channel)

    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS00);     // No prescaling

    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A = 159;            // Set the compare register to 160 ticks (zero based)

    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);   // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

ISR (TIMER0_COMPA_vect)
{
    // Toggle pin 0 port A
    PORTA ^= _BV(PORTA0);
}
