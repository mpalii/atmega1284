/**
 * @author Maksym Palii
 * @brief avr-gcc, led on
 * @date 2026 August 16
 */

// #define EXAMPLE_01

int main(void)
{
    /**
     * Using DDRA as 0x01
     * 000000a4 <main>:
     * a4:   81 e0           ldi     r24, 0x01       ; 1
     * a6:   80 93 01 00     sts     0x0001, r24     ; 0x800001 <__TEXT_REGION_LENGTH__+0x7e0001>
     * DOES NOT WORK
     */
    #ifdef EXAMPLE_01
    char *register_ddra_address = (char *) 0x01;
    *register_ddra_address = 0b00000001;
    #endif

    /**
     * Using assembly from EXAMPLE_01, with updated address
     * 000000a4 <main>:
     * a4:   81 e0           ldi     r24, 0x01       ; 1
     * a6:   80 93 21 00     sts     0x0021, r24     ; 0x800021 <__TEXT_REGION_LENGTH__+0x7e0021>
     * WORKS
     */
    #ifdef EXAMPLE_02
    __asm__("ldi r24, 0x01");
    __asm__("sts  0x21, r24");
    #endif

    /**
     * Using DDRA as 0x21
     * 000000a4 <main>:
     * a4:   81 e0           ldi     r24, 0x01       ; 1
     * a6:   81 b9           out     0x01, r24       ; 1
     * WORKS
     */
    #ifdef EXAMPLE_03
    char *register_ddra_address = (char *) 0x21;
    *register_ddra_address = 0b00000001;
    #endif

    /**
     * Using DDRA as 0x21
     * 000000a4 <main>:
     * a4:   08 9a           sbi     0x01, 0 ; 1
     * WORKS
     */
    #ifdef EXAMPLE_04
    char *register_ddra_address = (char *) 0x21;
    *register_ddra_address |= (1 << 0);
    #endif

    /**
     * Using DDRA as 0x01
     * 000000a4 <main>:
     * a4:   80 91 01 00     lds     r24, 0x0001     ; 0x800001 <__TEXT_REGION_LENGTH__+0x7e0001>
     * a8:   81 60           ori     r24, 0x01       ; 1
     * aa:   80 93 01 00     sts     0x0001, r24     ; 0x800001 <__TEXT_REGION_LENGTH__+0x7e0001>
     * DOES NOT WORK
     */
    #ifdef EXAMPLE_05
    char *register_ddra_address = (char *) 0x01;
    *register_ddra_address |= (1 << 0);
    #endif

    /**
     * Using assembly from EXAMPLE_05, with updated address
     * 000000a4 <main>:
     * a4:   20 91 21 00     lds     r18, 0x0021     ; 0x800021 <__TEXT_REGION_LENGTH__+0x7e0021>
     * a8:   21 60           ori     r18, 0x01       ; 1
     * aa:   20 93 21 00     sts     0x0021, r18     ; 0x800021 <__TEXT_REGION_LENGTH__+0x7e0021>
     * WORKS
     */
    #ifdef EXAMPLE_06
    __asm__ (
        "lds  r18, 0x21      \n\t"
        "ori  r18, 0x01      \n\t"
        "sts  0x21, r18      \n\t"
    );
    #endif

    /**
     * Using assembly from EXAMPLE_06, with updated instruction
     * 000000a4 <main>:
     * a4:   21 b1           in      r18, 0x01       ; 1
     * a6:   21 60           ori     r18, 0x01       ; 1
     * a8:   21 b9           out     0x01, r18       ; 1
     * WORKS
     */
    #ifdef EXAMPLE_07
    __asm__ (
        "in   r18, 0x01      \n\t"
        "ori  r18, 0x01      \n\t"
        "out  0x01, r18      \n\t"
    );
    #endif

    /**
     * Just inline sbi instruction
     * 000000a4 <main>:
     * a4:   08 9a           sbi     0x01, 0 ; 1
     * WORKS
     */
    #ifdef EXAMPLE_08
    __asm__("sbi 0x01, 0");
    #endif

    while (1)
    {
        // NOP
    }

    return 0;
}
