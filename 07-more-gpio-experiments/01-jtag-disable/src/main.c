/**
 * @author Maksym Palii
 * @brief JTAG disable
 * @version 1.0
 * @date 2026 January 31
 */

#define F_CPU (8000000UL)

#include <avr/io.h>
#include <util/delay.h>

static inline void disable_jtag(void)
{
    /**
     * Disable JTAG interface in order to make pins 2, 3, 4, 5 (Port C) as general purpose
     * see https://ww1.microchip.com/downloads/en/DeviceDoc/doc2593.pdf#G1.1375224
     */
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);
}

static inline void init_io_pins(void)
{
    // Configure data direction for pin 0 (port A) as OUTPUT
    DDRA |= _BV(DDRA0);
}

int main(void) 
{
    disable_jtag();
    init_io_pins();

    while (1)
    {
        PINA |= _BV(PINA0);
        _delay_ms(500);
    }

    return 0;
}   
  
