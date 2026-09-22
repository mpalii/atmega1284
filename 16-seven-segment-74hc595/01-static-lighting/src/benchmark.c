#include "benchmark.h"

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "drivers/gpio.h"
#include "drivers/shift_register.h"
#include "drivers/seven_segment.h"

/*
 * Test selector section
 */
// #define EX01_BASELINE                // 5 cycles
// #define EX02_SBI                     // 7 cycles
// #define EX03_DEC_0X0000              // 1245 cycles
// #define EX04_DEC_9999                // 1259 cycles
// #define EX05_DEC_0xFFFF              // 1250 cycles
// #define EX06_DEC_NO_LOOP_0X0000      // 1218 cycles
// #define EX07_DEC_NO_LOOP_9999        // 1232 cycles 
// #define EX08_DEC_NO_LOOP_0xFFFF      // 1223 cycles 
// #define EX09_DEC_NO_DIV_0X0000       // 435 cycles
// #define EX10_DEC_NO_DIV_9999         // 687 cycles
// #define EX11_DEC_NO_DIV_0xFFFF       // 599 cycles
// #define EX12_HEX_0X0000              // 430 cycles
// #define EX13_HEX_9999                // 412 cycles
// #define EX14_HEX_0xFFFF              // 406 cycles
// #define EX15_HEX_SHIFT_0X0000        // 433 cycles
// #define EX16_HEX_SHIFT_9999          // 415 cycles
// #define EX17_HEX_SHIFT_0xFFFF        // 409 cycles

void init_test(void)
{
    init_shift_register();
    init_seven_segment();
    sbi_ddr(LED);
}

void test(void)
{
    // Reset Timer/Counter1
    TCNT1 = 0;

    // Launch Timer/Counter1 without prescaling
    TCCR1B |= _BV(CS10);

#ifdef EX01_BASELINE
    // No actions
#endif

#ifdef EX02_SBI
    sbi_pin(LED);
#endif

#ifdef EX03_DEC_0X0000
    seven_segment_render_in_dec(0x0000);
#endif

#ifdef EX04_DEC_9999
    seven_segment_render_in_dec(9999);
#endif

#ifdef EX05_DEC_0xFFFF
    seven_segment_render_in_dec(0xFFFF);
#endif

#ifdef EX06_DEC_NO_LOOP_0X0000
    seven_segment_render_in_dec_no_loop(0);
#endif

#ifdef EX07_DEC_NO_LOOP_9999
    seven_segment_render_in_dec_no_loop(9999);
#endif

#ifdef EX08_DEC_NO_LOOP_0xFFFF
    seven_segment_render_in_dec_no_loop(0xFFFF);
#endif

#ifdef EX09_DEC_NO_DIV_0X0000
    seven_segment_render_in_dec_no_division(0);
#endif

#ifdef EX10_DEC_NO_DIV_9999
    seven_segment_render_in_dec_no_division(9999);
#endif

#ifdef EX11_DEC_NO_DIV_0xFFFF
    seven_segment_render_in_dec_no_division(0xFFFF);
#endif

#ifdef EX12_HEX_0X0000
    seven_segment_render_in_hex(0x0000);
#endif

#ifdef EX13_HEX_9999
    seven_segment_render_in_hex(9999);
#endif

#ifdef EX14_HEX_0xFFFF
    seven_segment_render_in_hex(0xFFFF);
#endif

#ifdef EX15_HEX_SHIFT_0X0000
    seven_segment_render_in_hex_shift(0x0000);
#endif

#ifdef EX16_HEX_SHIFT_9999
    seven_segment_render_in_hex_shift(9999);
#endif

#ifdef EX17_HEX_SHIFT_0xFFFF
    seven_segment_render_in_hex_shift(0xFFFF);
#endif

    // Stop Timer/Counter1
    TCCR1B &= (uint8_t) ~_BV(CS10);   

    // delay to see output first
    _delay_ms(1500);

    // render result
    seven_segment_render_in_dec(TCNT1);
    // seven_segment_render_in_dec_no_loop(TCNT1);
    // seven_segment_render_in_dec_no_division(TCNT1);
    // seven_segment_render_in_hex(TCNT1);
    // seven_segment_render_in_hex_shift(TCNT1);
}