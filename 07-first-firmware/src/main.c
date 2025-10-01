/**
 * @author Maksym Palii
 * @brief Simple bare metal 'Hello World' example without standard AVR libraries
 * @date 2025 October 01
 */

int main(void)
{
    /**
     * 1. Using DDRA as 0x01 - NOT WORK! (use 'disasm.sh')
     */
    // char *register_ddra_address = (char *) 0x01;
    // *register_ddra_address = 0b00000001;

    /**
     * 2. Using DDRA as 0x21
     */
    //char *register_ddra_address = (char *) 0x21;
    //*register_ddra_address = 0b00000001;

    /**
     * 3. Using DDRA as 0x21
     */
    // char *register_ddra_address = (char *) 0x21;
    // *register_ddra_address |= (1 >> 0);

    /**
     * 4. Using DDRA as 0x21 - short form
     */
    // *((char *) 0x21) = 0x01;

    /**
     * 5. Using DDRA as 0x21 - using assembly inline
     */
    // __asm__("ldi r24, 0x01");
    // __asm__("out 0x01, r24");

    /**
     * 6. Using DDRA as 0x21 - multiline assemply
     */
    // __asm__ (
    //     "ldi r24, 0x01      \n\t"
    //     "out 0x01, r24"
    // );

    while (1)
    {
        // NOP
        //__asm__("nop");
    }

    return 0;
}