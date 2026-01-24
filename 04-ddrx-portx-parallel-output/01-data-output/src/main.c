/**
 * @author Maksym Palii
 * @brief Simple parallel output
 * @version 1.0
 * @date 2026 January 22 
 */ 

#include <avr/io.h>

int main(void) 
{
    // Configure data direction for pins 0-7 (port D) as OUTPUT
    DDRD = 0xFF;  // aka 0b11111111 or 255

    char result = 0xFF;              // 0b11111111

    // uint8_t result = 0xFF;           // 0b11111111
    // uint8_t result = 0;              // 0b00000000
    // uint8_t result = 64;             // 0b01000000
    // uint8_t result = 255;            // 0b11111111
    // uint8_t result = 257;            // 0b00000001
    // uint8_t result = (uint8_t) 257;  // 0b00000001
    // uint8_t result = 6;              // 0b00000110

    // uint8_t result = 'h';            // ASCII 0x68
    // uint8_t result = 'H';            // ASCII 0x48
    // uint8_t result = 'G';            // ASCII 0x47
    // uint8_t result = '@';            // ASCII 0x40
    // uint8_t result = ' ';            // ASCII 0x20
    // uint8_t result = ';';            // ASCII 0x73
    // uint8_t result = 0xA9;           // Extended ASCII ©

    // uint8_t result = -2;             // 0b11111110
    // uint8_t result = (uint8_t) -2;   // 0b11111110
    // uint8_t result = -128;           // 0b10000000
    // uint8_t result = (uint8_t) -128; // 0b10000000

    // Show result in port D
    PORTD = result;

    while (1)
    {
        // NOP
    }
}