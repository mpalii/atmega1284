/**
 * @author Maksym Palii
 * @brief EEPROM read/write
 * @date 2026 October 23
 */

#include <avr/io.h>
#include <stdbool.h>

#define MEMORY_ADDRESS (0x0000)
// #define MEMORY_ADDRESS (0x03FF)
#define VALUE (0b11101011)

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

int main(void)
{
    // led on
    DDRA |= 1 << DDRA0;
    // output
    DDRB = 0xFF;

    EEPROM_write(MEMORY_ADDRESS, VALUE);
    PORTB = EEPROM_read(MEMORY_ADDRESS);

    while (true) 
    { 
        // NOP
    }
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
    ;
    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;

    // by default - Erase and Write in one operation (Atomic Operation)

    // Erase Only mode
    // EECR |= (1 << EEPM0);
    // Write Onky mode
    // EECR |= (1 << EEPM1);

    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
    ;
    /* Set up address register */
    EEAR = uiAddress;
    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    /* Return data from Data Register */
    return EEDR;
}