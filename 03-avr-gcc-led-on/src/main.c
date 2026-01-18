/**
 * @author Maksym Palii
 * @brief YL-34 led on
 * @date 2026 Jan 18
 */

int main(void)
{
    /**
     * 1. Using DDRA as 0x01 - NOT WORK!
     * ldi + sts
     */
    // char *register_ddra_address = (char *) 0x01;
    // *register_ddra_address = 0b00000001;

    /**
     * 2. Using DDRA as 0x21
     * ldi + out
     */
    // char *register_ddra_address = (char *) 0x21;
    // *register_ddra_address = 0b00000001;

    /**
     * 3. Using DDRA as 0x21
     * sbi
     */
    // char *register_ddra_address = (char *) 0x21;
    // *register_ddra_address |= (1 << 0);

    /**
     * 4. Using DDRA as 0x21 - short form
     * ldi + out
     */
    // *((char *) 0x21) = 0x01;

    /**
     * 5. Using DDRA as 0x21 - short form
     * sbi
     */
    // *((char *) 0x21) |= (1 << 0);

    /**
     * 6. Using DDRA as 0x21 - using assembly inline
     */
    // __asm__("ldi r24, 0x01");
    // __asm__("out 0x01, r24");

    /**
     * 7. Using DDRA as 0x21 - multiline assemply
     */
    // __asm__ (
    //     "ldi r24, 0x01      \n\t"
    //     "out 0x01, r24"
    // );

    /**
     * 8. Using DDRA as 0x01 - NOT WORK!
     * lds + ori + sts
     */
    // char *register_ddra_address = (char *) 0x01;
    // *register_ddra_address |= (1 << 0);

    while (1)
    {
        // NOP
    }

    return 0;
}
