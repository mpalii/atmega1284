/**
 * @author Maksym Palii
 * @brief Timer 0 usage example, 50kHz generator
 * @version 1.0
 * @date 2025 October 26
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>

void init_io_pins(void);
void init_timer_0(void);

ISR (TIMER0_COMPA_vect)
{
	// Toggle pin 0 port A
	PORTA ^= _BV(PORTA0);
}

// ISR (TIMER0_COMPA_vect, ISR_NAKED)
// {
//     // Toggle pin 0 port A
//     PINA |= _BV(PORTA0);
//     // Interrupt return
//     reti();
// }

int main(void)
{
    init_io_pins();
    init_timer_0();
    sei();
	
    while (true) 
    { 
        // NOP
    }
}

void init_io_pins(void)
{
    // Set port A pin 0 as output
    DDRA |= _BV(DDA0);
}

/****************************************************************************/
/* Set up timer 0 for 10 uSec timebase                                      */
/* (1 (prescaler) * 80 (OCR0A + 1)) / 8_000_000 MHz = 0.00001Sec = 10uSec   */
/****************************************************************************/
void init_timer_0(void)
{	
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);   // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS00);    // No prescaling
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A = 79;			   //set the compare reg to 80 ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);  // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}
