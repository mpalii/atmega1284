/**
 * @author Maksym Palii
 * @brief Simple parallel output
 * @date 2026 August 18
 */ 

#include <avr/io.h>

void ex1_parallel_output_test(void);
void ex2_parallel_output_data(void);
void ex3_parallel_output_type_layout(void);
void ex4_parallel_output_endianess(void);
void ex5_parallel_output_utf8(void);

int main(void)
{
    // Configure data direction for pins 0-7 (port D) as OUTPUT
    DDRD = 0xFF;  // aka 0b11111111 or 255

    // ex1_parallel_output_test();
    // ex2_parallel_output_data();
	// ex3_parallel_output_type_layout();
	// ex4_parallel_output_endianess();
	// ex5_parallel_output_utf8();

    while (1) 
    {
        // NOP
    }

    return 0;
}

void ex1_parallel_output_test(void)
{
    // PORTD = 0b00000001;
    // PORTD = 0b00000010;
    // PORTD = 0b00000100;
    // PORTD = 0b00001000;
    // PORTD = 0b00010000;
    // PORTD = 0b00100000;
    // PORTD = 0b01000000;
    // PORTD = 0b10000000;
}

void ex2_parallel_output_data(void)
{
    // char result = 0b11111111;
	// char result = 0xFF;              // 0b11111111
	// char result = 255;               // 0b11111111
	// char result = 256;               // 0b00000000	warning: unsigned conversion from 'int' to 'char' changes value from '256' to '0' [-Woverflow]
	// char result = (char) 256;        // 0b00000000 
	// char result = -1;                // 0b11111111
	// char result = -510;              // 0b00000010	warning: unsigned conversion from 'int' to 'char' changes value from '-510' to '2' [-Woverflow] 11111110 00000010
	// char result = (char) -510;       // 0b00000010

	/*
     * To continue experiment enable extra warning flags:
     * -Wextra -Wconversion -Wsign-conversion -Woverflow 
     */ 
    // char result = 0b11111111;
	// char result = 0xFF;             	// 0b11111111
	// char result = 255;				// 0b11111111
    // char result = -1;				// 0b11111111

	// uint8_t result = 0xFF;          	// 0b11111111
	// uint8_t result = 0;             	// 0b00000000
	// uint8_t result = 65;            	// 0b01000001
	// uint8_t result = 255;           	// 0b11111111
	// uint8_t result = 257;           	// 0b00000001	warning: unsigned conversion from 'int' to 'uint8_t' {aka 'unsigned char'} changes value from '257' to '1' [-Woverflow]
	// uint8_t result = (uint8_t) 257; 	// 0b00000001
	// uint8_t result = 6;             	// 0b00000110

	// uint8_t result = 'h';           	// ASCII 0x68
	// uint8_t result = 'H';           	// ASCII 0x48
	// uint8_t result = 'G';           	// ASCII 0x47
	// uint8_t result = '@';           	// ASCII 0x40
	// uint8_t result = ' ';           	// ASCII 0x20
	// uint8_t result = ';';           	// ASCII 0x3B
	// uint8_t result = 0xA9;          	// Extended ASCII ©
	// uint8_t result = '©';          	// Extended ASCII 0xA9
	// uint8_t result = (uint8_t) '©';  // https://www.compart.com/en/unicode/U+00A9 the source code is in UTF-8 encoding

	// uint8_t result = -2;            	// 0b11111110	warning: unsigned conversion from 'int' to 'uint8_t' {aka 'unsigned char'} changes value from '-2' to '254' [-Wsign-conversion]
	// uint8_t result = (uint8_t) -2;  	// 0b11111110
	// uint8_t result = -128;          	// 0b10000000	warning: unsigned conversion from 'int' to 'uint8_t' {aka 'unsigned char'} changes value from '-128' to '128' [-Wsign-conversion]
	// uint8_t result = (uint8_t) -128;	// 0b10000000

	// PORTD = result;
}

void ex3_parallel_output_type_layout(void)
{
	// uint8_t result;

	// 1 byte
	// result = sizeof(char);
	// result = sizeof(unsigned char);
	// result = sizeof(signed char);

	// 2 bytes
	// result = sizeof(short int);
	// result = sizeof(short unsigned int);
	// result = sizeof(short signed int);

	// 2 bytes
	// result = sizeof(int);
	// result = sizeof(unsigned int);
	// result = sizeof(signed int);

	// 4 bytes
	// result = sizeof(long int);
	// result = sizeof(long unsigned int);
	// result = sizeof(long signed int);

	// 8 bytes
	// result = sizeof(long long int);
	// result = sizeof(long long unsigned int);
	// result = sizeof(long long signed int);

	// 4 bytes
	// result = sizeof(float);
	// result = sizeof(double);

	// 8 bytes
	// result = sizeof(long double);

	// 1 byte
	// result = sizeof(void);

	// 2 bytes
	// result = sizeof(char *);
	// result = sizeof(int *);
	// result = sizeof(long *);
	// result = sizeof(long long *);
	// result = sizeof(float *);
	// result = sizeof(double *);
	// result = sizeof(void *);

	// 1 byte
	// result = sizeof(uint8_t);
	// result = sizeof(int8_t);

	// 2 bytes
	// result = sizeof(uint16_t);
	// result = sizeof(int16_t);

	// 4 bytes
	// result = sizeof(uint32_t);
	// result = sizeof(int32_t);

	// 8 bytes
	// result = sizeof(uint64_t);
	// result = sizeof(int64_t);

	// 2 bytes
	// enum EState{STATE1, STATE2, STATE3};
	// result = sizeof(STATE1);

    // 4 bytes
	// result = sizeof(6);
	// result = sizeof(-1);
	// result = sizeof(0xFF);
	// result = sizeof(0xffFF);
	// result = sizeof(0xFFffFF);
	// result = sizeof(0xffFFffFF);
	// result = sizeof(-40000);
	// result = sizeof(2147483647);

	// 8 bytes
	// result = sizeof(2147483648);
	// result = sizeof(0xFFffFFffFF);
	// result = sizeof(0xffFFffFFffFFffFF);
	// result = sizeof(0xAAbbCCddEEffAAbbCC);  // warning: integer constant is too large for its type

    // 18 bytes
	// int array[] = { 0xAA, 0xbb, 0xCC, 0xdd, 0xEE, 0xff, 0xAA, 0xbb, 0xCC};
	// result = sizeof(array);

	// 9 bytes
	// char array[] = { 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x0A, 0x0B, 0x0C};
	// result = sizeof(array);

	// 2 bytes
	// result = sizeof('a');
	// result = sizeof(';');
	// result = sizeof('©');   // warning: multi-character character constant [-Wmultichar]

	// result = sizeof(U'©');					// 4 bytes
	// result = sizeof("©");					// 3 bytes
	// result = sizeof("a");					// 2 bytes (int)
	// result = sizeof((char) 'a');				// 1 byte
	// result = sizeof("");						// 1 byte
	// result = sizeof("Hello World");			// 12 bytes
	// result = sizeof("€");					// 4 bytes
	// result = sizeof("Й");					// 3 bytes
	// result = sizeof(1UL);					// 4 bytes
	// result = sizeof(1ULL);					// 8 bytes

	// PORTD = result;
}

void ex4_parallel_output_endianess(void)
{
	// MSB[0000 0010] LSB[0100 0000] or (512 + 64)
	// uint16_t value = 576;

	// get pointer of value
	// uint8_t *first_byte_address = (uint8_t *) &value;

	// show results
	// uint8_t result = *first_byte_address;		// LSB[0100 0000]
	// uint8_t result = *(first_byte_address + 1); 	// MSB[0000 0010]

	// PORTD = result;
}

void ex5_parallel_output_utf8(void)
{
	// char *copyright = "©";
	// char *copyright = "\u00A9";

	// show results
	// uint8_t result = (uint8_t) *copyright;					// 0xC2
	// uint8_t result = (uint8_t) *(copyright + 1);				// 0xA9
	// uint8_t result = (uint8_t) *(copyright + 2);				// 0x00

	// uint8_t result = (uint8_t) "©"[0];		// 0xC2
	// uint8_t result = (uint8_t) "©"[1];		// 0xA9
	// uint8_t result = (uint8_t) "©"[2];		// 0x00

	// PORTD = result;
}