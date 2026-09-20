#include <avr/io.h>

/*
 * Fuses configuration:
 * - JTAG disable
 * - external crystal/resonator
 * - no divider
 * 
 * lfuse=0xFF
 * hfuse=0xD9
 * efuse=0xFF
 */

FUSES =
{
    .low = 0xFF
        // & FUSE_CKDIV8
        // & FUSE_CKOUT
        // & FUSE_SUT_CKSEL5
        // & FUSE_SUT_CKSEL4
        // & FUSE_SUT_CKSEL3
        // & FUSE_SUT_CKSEL2
        // & FUSE_SUT_CKSEL1
        // & FUSE_SUT_CKSEL0
    ,

    .high = 0xFF
        // & FUSE_OCDEN
        // & FUSE_JTAGEN
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
