/**
 * @author Maksym Palii
 * @brief Extenal Interrupt - benchmarking with Timer/Counter 1
 * @date 2026 September 23
 */

#include <stdlib.h>
#include <avr/interrupt.h>

#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"

ISR(INT0_vect)
{
    // 2 machine cycles
    sbi_ddr(LED);           
}

int main(void)
{
    init_shift_register();
    init_seven_segment();

    // Init External Interrupt 0 pin - output driven high
    sbi_ddr(INT0_PIN);
    sbi_port(INT0_PIN);

    // Configure external interrupts
    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);
    
    // Enable global interrupts
    // sei();

    // Launch Timer/Counter1 without prescaling
    TCCR1B |= _BV(CS10);

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

    // Stop Timer/Counter1
    TCCR1B &= (uint8_t) ~_BV(CS10);   

    // render result
    seven_segment_render(TCNT1);

    while(1)
    {

    }

    return 0;
}

// "baseline"       = 5
// "main logic"     = 2 + 3 + 3 = 8
// total            = 13

// total + interrupt    = 25
// 13 + interrupt       = 25
// interrupt            = 12

// vector table enter   = 3
// jmp                  = 3
// sbi ("logic")        = 2 
// reti                 = 4

// pure interrupt       = 3 + 3 + 4 = 13
