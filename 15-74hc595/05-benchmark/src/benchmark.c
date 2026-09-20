#include "benchmark.h"

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "drivers/gpio.h"
#include "drivers/shift_register.h"

/*
 * Test selector section
 */
#define EX01_BASELINE
// #define EX02_SBI
// #define EX03_NOP
// #define EX04_NOP_5_TIMES
// #define EX05_DELAY_10_MICROSECONDS
// #define EX06_DELAY_3_MILLISECONDS
// #define EX07_SHIFT_0X00
// #define EX08_SHIFT_0XFF
// #define EX09_SHIFT_WITH_MASKS_0X00
// #define EX10_SHIFT_WITH_MASKS_0XFF
// #define EX11_SHIFT_WITH_SHIFT_0X00
// #define EX12_SHIFT_WITH_SHIFT_0XFF
// #define EX13_SHIFT_0X0000
// #define EX14_SHIFT_0XFFFF
// #define EX15_SHIFT_WITH_SHIFT_0X0000
// #define EX16_SHIFT_WITH_SHIFT_0XFFFF
// #define EX17_SHIFT_PER_BYTE_0X0000
// #define EX18_SHIFT_PER_BYTE_0XFFFF
// #define EX19_SHIFT_PER_BYTE_0X00
// #define EX20_SHIFT_PER_BYTE_0XFF

void init_test(void)
{
    init_shift_register();
    sbi_ddr(LED);
}

void test(void)
{
    TCCR1B |= _BV(CS10);     // Launch Timer/Counter1 without prescaling

// Total time: 5 cycles; 0000 0101
// Logic time: 0 cycles
#ifdef EX01_BASELINE
    // No actions
#endif

// Total time: 7 cycles; 0000 0111
// Logic time: 2 cycles
#ifdef EX02_SBI
    sbi_pin(LED);
#endif

// Total time: 6 cycles; 0000 0110
// Logic time: 1 cycle
#ifdef EX03_NOP
    __asm__("nop");
#endif

// Total time: 10 cycles; 0000 1010
// Logic time: 5 cycles
#ifdef EX04_NOP_5_TIMES
    __asm__ (
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
    );
#endif

// Total time: 85 cycles; 0101 0101
// Logic time: 80 cycles
#ifdef EX05_DELAY_10_MICROSECONDS
    _delay_us(10);
#endif

// Actual time: 24005 cycles; 0101 1101 1100 0101
// Logic time: 24000 cycles
#ifdef EX06_DELAY_3_MILLISECONDS
    _delay_ms(3);
#endif

// Total time: 344 cycles; 0000 0001 0101 1000
// Logic time: 339 cycles
#ifdef EX07_SHIFT_0X00
    shift(0x00);
#endif

// Total time: 320 cycles; 0000 0001 0100 0000
// Logic time: 315 cycles
#ifdef EX08_SHIFT_0XFF
    shift(0xFF);
#endif

// Total time: 106 cycles; 0110 1010
// Logic time: 101 cycles
#ifdef EX09_SHIFT_WITH_MASKS_0X00
    shift_with_masks(0x00);
#endif

// Total time: 82 cycles; 0101 0010
// Logic time: 77 cycles
#ifdef EX10_SHIFT_WITH_MASKS_0XFF
    shift_with_masks(0xFF);
#endif

// Total time: 138 cycles; 1000 1010
// Logic time: 135 cycles
#ifdef EX11_SHIFT_WITH_SHIFT_0X00
    shift_with_shift(0x00);
#endif

// Total time: 114 cycles; 0111 0010
// Logic time: 109 cycles
#ifdef EX12_SHIFT_WITH_SHIFT_0XFF
    shift_with_shift(0xFF);
#endif

// Total time: 1023 cycles; 0000 0011 1111 1111
// Logic time: 1018 cycles
#ifdef EX13_SHIFT_0X0000
    shift_uint16(0x0000);
#endif

// Total time: 975 cycles; 0000 0011 1100 1111
// Logic time: 970 cycles
#ifdef EX14_SHIFT_0XFFFF
    shift_uint16(0xFFFF);
#endif

// Total time: 276 cycles; 0000 0001 0001 0100
// Logic time: 271 cycles
#ifdef EX15_SHIFT_WITH_SHIFT_0X0000
    shift_with_shift_uint16(0x0000);
#endif

// Total time: 228 cycles; 1110 0100
// Logic time: 223 cycles
#ifdef EX16_SHIFT_WITH_SHIFT_0XFFFF
    shift_with_shift_uint16(0xFFFF);
#endif

// Total time: 211 cycles; 1101 0011
// Logic time: 206 cycles
#ifdef EX17_SHIFT_PER_BYTE_0X0000
    shift_byte(0x00);
    shift_byte(0x00);
    rclk_pulse();
#endif

// Total time: 163 cycles; 1010 0011
// Logic time: 158 cycles
#ifdef EX18_SHIFT_PER_BYTE_0XFFFF
    shift_byte(0xFF);
    shift_byte(0xFF);
    rclk_pulse();
#endif

// Total time: 114 cycles; 0111 0010
// Logic time: 109 cycles
#ifdef EX19_SHIFT_PER_BYTE_0X00
    shift_byte(0x00);
    rclk_pulse();
#endif

// Total time: 90 cycles; 0101 1010
// Logic time: 85 cycles
#ifdef EX20_SHIFT_PER_BYTE_0XFF
    shift_byte(0xFF);
    rclk_pulse();
#endif

    TCCR1B &= (uint8_t) ~_BV(CS10);   // Stop Timer/Counter1

    shift(TCNT1L);
    shift(TCNT1H);
}