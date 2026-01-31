/**
 * @author Maksym Palii
 * @brief Timer 0 usage example, 4MHz generator, 8MHz frequency
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
    // Set port B pin 3 as output (OC0A)
    DDRB |= _BV(DDRB3);
}

/*******************************************************************************/
/* Set up timer 0 for toggling OC0A on Compare Match - PB3                     */
/* (1 (prescaler) * 1 (OCR0B + 1)) / 8_000_000 MHz = 0.000000125Sec = 125nSec  */
/*******************************************************************************/
void init_timer_0(void)
{
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A = 0;                          // Set the compare register to 1 ticks (zero based)

    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(COM0A0) | _BV(WGM01);  // Toggle OC0A on Compare Match + Clear Timer on Compare Match (CTC) mode (only works with channel)

    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS00);                 // Start timer 0 with no prescaling
}