/**
 * @author Maksym Palii
 * @brief Button (keyboard) matrix
 * @version 1.0
 * @date 2026 February 18
 */

#define F_CPU               (8000000UL)
#define STABILIZATION_TIME  (5)

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
    // Port B as output (led bar 1)
    DDRB = 0xFF;
    // Port D as output (led bar 2)
    DDRD = 0xFF;
}

uint8_t get_matrix_state(void)
{
    uint8_t result_state = 0x00;

    // Enable pull-up resistors for the rows
    PORTC = 0xF0;
    // Set driven low for the columns
    DDRC = 0x0F;
    _delay_us(STABILIZATION_TIME);

    // Get rows state
    uint8_t rows_state = PINC & 0xF0;
    result_state |= rows_state;

    // High-Z
    PORTC = 0x00;
    DDRC = 0x00;

    // Enable pull-up resistors for the columns
    PORTC = 0x0F;
    // Set driven low for the rows
    DDRC = 0xF0;
    _delay_us(STABILIZATION_TIME);

    // Get columns state
    uint8_t columns_state = PINC & 0x0F;
    result_state |= columns_state;

    // High-Z
    PORTC = 0x00;
    DDRC = 0x00;

    return ~result_state;
}

void handle_button(uint8_t pins_state, uint8_t button_mask, bool * button_was_pressed, volatile uint8_t * port_led, uint8_t pin_led)
{
    bool is_pressed = (pins_state & button_mask) == button_mask;

    // check whether button was pressed
    if (is_pressed && !(*button_was_pressed))
    {
        *button_was_pressed = true;
        *port_led ^= _BV(pin_led);
    }
    
    // check whether button was released
    if (!is_pressed && *button_was_pressed)
    {
        *button_was_pressed  = false;
    }
}

int main(void)
{
    init_pins();

    while (true)
    {
        uint8_t matrix_state = get_matrix_state();

        /* Button B1 */
        handle_button(matrix_state, 0b10001000, &button_01_was_pressed, &PORTB, PB0);
        /* Button B2 */
        handle_button(matrix_state, 0b10000100, &button_02_was_pressed, &PORTB, PB1);
        /* Button B3 */
        handle_button(matrix_state, 0b10000010, &button_03_was_pressed, &PORTB, PB2);
        /* Button BA */
        handle_button(matrix_state, 0b10000001, &button_04_was_pressed, &PORTB, PB3);

        /* Button B4 */
        handle_button(matrix_state, 0b01001000, &button_05_was_pressed, &PORTB, PB4);
        /* Button B5 */
        handle_button(matrix_state, 0b01000100, &button_06_was_pressed, &PORTB, PB5);
        /* Button B6 */
        handle_button(matrix_state, 0b01000010, &button_07_was_pressed, &PORTB, PB6);
        /* Button BB */
        handle_button(matrix_state, 0b01000001, &button_08_was_pressed, &PORTB, PB7);

        /* Button B7 */
        handle_button(matrix_state, 0b00101000, &button_09_was_pressed, &PORTD, PD0);
        /* Button B8 */
        handle_button(matrix_state, 0b00100100, &button_10_was_pressed, &PORTD, PD1);
        /* Button B9 */
        handle_button(matrix_state, 0b00100010, &button_11_was_pressed, &PORTD, PD2);
        /* Button BC */
        handle_button(matrix_state, 0b00100001, &button_12_was_pressed, &PORTD, PD3);

        /* Button B* */
        handle_button(matrix_state, 0b00011000, &button_13_was_pressed, &PORTD, PD4);
        /* Button B0 */
        handle_button(matrix_state, 0b00010100, &button_14_was_pressed, &PORTD, PD5);
        /* Button B# */
        handle_button(matrix_state, 0b00010010, &button_15_was_pressed, &PORTD, PD6);
        /* Button BD */
        handle_button(matrix_state, 0b00010001, &button_16_was_pressed, &PORTD, PD7);

        // simpliest software debounce
        _delay_ms(20);
    }

    return 0;
}