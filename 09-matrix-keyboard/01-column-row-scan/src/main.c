/**
 * @author Maksym Palii
 * @brief Button (keyboard) matrix
 * @version 1.0
 * @date 2026 February 18
 */

#define F_CPU (8000000UL)
#define STABILIZATION_TIME (5)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

// column 1
bool button_01_was_pressed = false;
bool button_02_was_pressed = false;
bool button_03_was_pressed = false;
bool button_04_was_pressed = false;
// column 2
bool button_05_was_pressed = false;
bool button_06_was_pressed = false;
bool button_07_was_pressed = false;
bool button_08_was_pressed = false;
// column 3
bool button_09_was_pressed = false;
bool button_10_was_pressed = false;
bool button_11_was_pressed = false;
bool button_12_was_pressed = false;
// column A
bool button_13_was_pressed = false;
bool button_14_was_pressed = false;
bool button_15_was_pressed = false;
bool button_16_was_pressed = false;

static inline void init_pins(void)
{
    // Enable pull-up resistors for the rows
    PORTC |= _BV(PC7) | _BV(PC6) | _BV(PC5) | _BV(PC4);
    // Port B as output (led bar 1)
    DDRB = 0xFF;
    // Port D as output (led bar 2)
    DDRD = 0xFF;
}

/*=======================================================================*/
static inline void check_column_1(void)
{
    /* Enable column 1 (buttons: B1, B4, B7, B*) */
    DDRC |= _BV(PC3);
    _delay_us(STABILIZATION_TIME);
    
    /* Button B1 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC7) && !button_01_was_pressed)
    {
        button_01_was_pressed = true;
        PORTB ^= _BV(PB0);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC7) && button_01_was_pressed)
    {
        button_01_was_pressed = false;
    }

    /* Button B4 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC6) && !button_02_was_pressed)
    {
        button_02_was_pressed = true;
        PORTB ^= _BV(PB4);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC6) && button_02_was_pressed)
    {
        button_02_was_pressed = false;
    }

    /* Button B7 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC5) && !button_03_was_pressed)
    {
        button_03_was_pressed = true;
        PORTD ^= _BV(PD0);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC5) && button_03_was_pressed)
    {
        button_03_was_pressed = false;
    }

    /* Button B* */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC4) && !button_04_was_pressed)
    {
        button_04_was_pressed = true;
        PORTD ^= _BV(PD4);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC4) && button_04_was_pressed)
    {
        button_04_was_pressed = false;
    }

    /* Disable column 1 (buttons: B1, B4, B7, B*) */
    DDRC &= (uint8_t) ~_BV(PC3);
}

/*=======================================================================*/
static inline void check_column_2(void)
{
    /* Enable column 2 (buttons: B2, B5, B8, B0) */
    DDRC |= _BV(PC2);
    _delay_us(STABILIZATION_TIME);
    
    /* Button B2 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC7) && !button_05_was_pressed)
    {
        button_05_was_pressed = true;
        PORTB ^= _BV(PB1);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC7) && button_05_was_pressed)
    {
        button_05_was_pressed = false;
    }

    /* Button B5 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC6) && !button_06_was_pressed)
    {
        button_06_was_pressed = true;
        PORTB ^= _BV(PB5);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC6) && button_06_was_pressed)
    {
        button_06_was_pressed = false;
    }

    /* Button B8 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC5) && !button_07_was_pressed)
    {
        button_07_was_pressed = true;
        PORTD ^= _BV(PD1);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC5) && button_07_was_pressed)
    {
        button_07_was_pressed = false;
    }

    /* Button B0 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC4) && !button_08_was_pressed)
    {
        button_08_was_pressed = true;
        PORTD ^= _BV(PD5);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC4) && button_08_was_pressed)
    {
        button_08_was_pressed = false;
    }

    /* Disable column 2 (buttons: B2, B5, B8, B0) */
    DDRC &= (uint8_t) ~_BV(PC2);
}

/*=======================================================================*/
static inline void check_column_3(void)
{
    /* Enable column 3 (buttons: B3, B6, B9, B#) */
    DDRC |= _BV(PC1);
    _delay_us(STABILIZATION_TIME);
    
    /* Button B3 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC7) && !button_09_was_pressed)
    {
        button_09_was_pressed = true;
        PORTB ^= _BV(PB2);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC7) && button_09_was_pressed)
    {
        button_09_was_pressed = false;
    }

    /* Button B6 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC6) && !button_10_was_pressed)
    {
        button_10_was_pressed = true;
        PORTB ^= _BV(PB6);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC6) && button_10_was_pressed)
    {
        button_10_was_pressed = false;
    }

    /* Button B9 */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC5) && !button_11_was_pressed)
    {
        button_11_was_pressed = true;
        PORTD ^= _BV(PD2);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC5) && button_11_was_pressed)
    {
        button_11_was_pressed = false;
    }

    /* Button B# */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC4) && !button_12_was_pressed)
    {
        button_12_was_pressed = true;
        PORTD ^= _BV(PD6);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC4) && button_12_was_pressed)
    {
        button_12_was_pressed = false;
    }

    /* Disable column 3 (buttons: B3, B6, B9, B#) */
    DDRC &= (uint8_t) ~_BV(PC1);
}

/*=======================================================================*/
static inline void check_column_A(void)
{
    /* Enable column A (buttons: BA, BB, BC, BD) */
    DDRC |= _BV(PC0);
    _delay_us(STABILIZATION_TIME);
    
    /* Button BA */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC7) && !button_13_was_pressed)
    {
        button_13_was_pressed = true;
        PORTB ^= _BV(PB3);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC7) && button_13_was_pressed)
    {
        button_13_was_pressed = false;
    }

    /* Button BB */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC6) && !button_14_was_pressed)
    {
        button_14_was_pressed = true;
        PORTB ^= _BV(PB7);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC6) && button_14_was_pressed)
    {
        button_14_was_pressed = false;
    }

    /* Button BC */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC5) && !button_15_was_pressed)
    {
        button_15_was_pressed = true;
        PORTD ^= _BV(PD3);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC5) && button_15_was_pressed)
    {
        button_15_was_pressed = false;
    }

    /* Button BD */
    // check whether button was pressed
    if (bit_is_clear(PINC, PC4) && !button_16_was_pressed)
    {
        button_16_was_pressed = true;
        PORTD ^= _BV(PD7);
    }
    
    // check whether button was released
    if (bit_is_set(PINC, PC4) && button_16_was_pressed)
    {
        button_16_was_pressed = false;
    }

    /* Disable column A (buttons: BA, BB, BC, BD) */
    DDRC &= (uint8_t) ~_BV(PC0);
}

int main(void)
{
    init_pins();

    while (true)
    {
        check_column_1();
        check_column_2();
        check_column_3();
        check_column_A();

        // simpliest software debounce
        _delay_ms(20);
    }

    return 0;
}