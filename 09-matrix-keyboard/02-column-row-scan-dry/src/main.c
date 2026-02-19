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

void handle_button(volatile uint8_t * pin_port, uint8_t pin, bool * button_was_pressed, volatile uint8_t * port_led, uint8_t pin_led)
{
    bool input_high = bit_is_set(*pin_port, pin);

    // check whether button was pressed
    if (!input_high && !(*button_was_pressed))
    {
        *button_was_pressed = true;
        *port_led ^= _BV(pin_led);
    }
    
    // check whether button was released
    if (input_high && *button_was_pressed)
    {
        *button_was_pressed  = false;
    }
}

/*=======================================================================*/
static inline void check_column_1(void)
{
    /* Enable column 1 (buttons: B1, B4, B7, B*) */
    DDRC |= _BV(PC3);
    _delay_us(STABILIZATION_TIME);
    
    /* Button B1 */
    handle_button(&PINC, PC7, &button_01_was_pressed, &PORTB, PB0);
    /* Button B4 */
    handle_button(&PINC, PC6, &button_02_was_pressed, &PORTB, PB4);
    /* Button B7 */
    handle_button(&PINC, PC5, &button_03_was_pressed, &PORTD, PD0);
    /* Button B* */
    handle_button(&PINC, PC4, &button_04_was_pressed, &PORTD, PD4);

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
    handle_button(&PINC, PC7, &button_05_was_pressed, &PORTB, PB1);
    /* Button B5 */
    handle_button(&PINC, PC6, &button_06_was_pressed, &PORTB, PB5);
    /* Button B8 */
    handle_button(&PINC, PC5, &button_07_was_pressed, &PORTD, PD1);
    /* Button B0 */
    handle_button(&PINC, PC4, &button_08_was_pressed, &PORTD, PD5);

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
    handle_button(&PINC, PC7, &button_09_was_pressed, &PORTB, PB2);
    /* Button B6 */
    handle_button(&PINC, PC6, &button_10_was_pressed, &PORTB, PB6);
    /* Button B9 */
    handle_button(&PINC, PC5, &button_11_was_pressed, &PORTD, PD2);
    /* Button B# */
    handle_button(&PINC, PC4, &button_12_was_pressed, &PORTD, PD6);

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
    handle_button(&PINC, PC7, &button_13_was_pressed, &PORTB, PB3);
    /* Button BB */
    handle_button(&PINC, PC6, &button_14_was_pressed, &PORTB, PB7);
    /* Button BC */
    handle_button(&PINC, PC5, &button_15_was_pressed, &PORTD, PD3);
    /* Button BD */
    handle_button(&PINC, PC4, &button_16_was_pressed, &PORTD, PD7);

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