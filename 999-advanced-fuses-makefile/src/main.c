/**
 * @author Maksym Palii
 * @brief Advanced fuses configuration
 * @version 1.0
 * @date 2026-02-11
 */

#define F_CPU (1000000UL)

#include <avr/io.h>
#include <util/delay.h>

FUSES =
{
    .low = 0xFF
        & FUSE_CKDIV8
        // & FUSE_CKOUT
        // & FUSE_SUT_CKSEL5
        & FUSE_SUT_CKSEL4
        & FUSE_SUT_CKSEL3
        & FUSE_SUT_CKSEL2
        // & FUSE_SUT_CKSEL1
        & FUSE_SUT_CKSEL0
    ,

    .high = 0xFF
        // & FUSE_OCDEN
        & FUSE_JTAGEN
        & FUSE_SPIEN
        // & FUSE_WDTON
        // & FUSE_EESAVE
        & FUSE_BOOTSZ1
        & FUSE_BOOTSZ0
        // & FUSE_BOOTRST
    ,

    .extended = 0xFF 
        // & FUSE_BODLEVEL2 
        // & FUSE_BODLEVEL1 
        // & FUSE_BODLEVEL0
    ,
};


int main(void)
{
    DDRA |= _BV(DDRA0);

    while(1)
    {
        PINA |= _BV(PINA0);
        _delay_ms(500);
    }

    return 0;
}
