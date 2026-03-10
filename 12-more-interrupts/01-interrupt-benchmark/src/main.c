/**
 * @author Maksym Palii
 * @brief Extenal Interrupt - benchmarking with Timer/Counter 0
 * @version 1.0
 * @date 2026-03-10
 */

#include <stdlib.h>
#include <avr/interrupt.h>
#include "drivers/sn74hc595.h"

ISR(INT0_vect)
{
    // 2 machine cycles
    sbi_ddr(LED);           
}

int main(void)
{
    // Init shift register
    sn74hc595_init();

    // Init External Interrupt 0 pin - output driven high
    sbi_ddr(INT0_PIN);
    sbi_port(INT0_PIN);

    // Configure external interrupts
    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);
    
    // Enable global interrupts
    // sei();

    // Start Timer/Counter0 without prescaling
    TCCR0B = _BV(CS00);

    // trigger external interrupt 2
    cbi_port(INT0_PIN);     // 2

    __asm__ (
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
    );                      // 3

    __asm__ __volatile__ (
        "jmp .+0 \n\t"
    );                      // 3

    // get execution time
    uint8_t time = TCNT0;     

    // Stop Timer/Counter0 
    TCCR0B = 0x00;

    // render result
    sn74hc595_shift(0x00);
    sn74hc595_shift(time);

    while(1)
    {

    }

    return 0;
}


// "main logic"     = 2 + 3 + 3 = 8
// with interrupt   = 20
// (I + 2) + 8      = 20

// pure interrupt   = 10
// int enter        = 3
// jmp              = 3
// sbi - business logic
// reti             = 4
