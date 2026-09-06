#!/bin/bash
# C project initializer

if [ -e Makefile ] || [ -e src/main.c ] || [ -e src/drivers/gpio.h ]; then
    echo "Project already initialized"
    exit 1
fi

mkdir -p src/drivers

# main.c
cat > "src/main.c" <<EOF
/**
 * @author Maksym Palii
 * @brief Simple project
 * @date $(date '+%Y %B %d')
 */

#include "drivers/gpio.h"

int main(void)
{
    while(1)
    {

    }

    return 0;
}
EOF

# Makefile
cat > "Makefile" <<'EOF'
# Makefile
DESTINATION  = firmware
DEVICE       = atmega1284
PROGRAMMER   = avrispmkII

# Source files
SOURCES = 									\
    src/main.c 								\

# Object files
OBJECTS = $(patsubst src/%.c, target/%.o, $(SOURCES))

default: build 

build: clean $(OBJECTS)
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -Wextra -Wconversion -Wsign-conversion -Woverflow -o ./target/$(DESTINATION).elf $(OBJECTS)
	@avr-objcopy --input-target elf32-avr --output-target ihex --verbose ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

./target/%.o: ./src/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -Wextra -Wconversion -Wsign-conversion -Woverflow -c $< -o $@

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

check:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE)

erease:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -e

upload:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U flash:w:./target/$(DESTINATION).hex:i

disasm: ./target/$(DESTINATION).elf
	@avr-objdump --section-headers ./target/$(DESTINATION).elf
	@avr-objdump --disassemble ./target/$(DESTINATION).elf
	@avr-objdump --full-contents --section=.data ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@avr-size --format=AVR --mcu=$(DEVICE) ./target/$(DESTINATION).elf

dump:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U flash:r:-:h

fuses-default:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xff:m 

fuses-no-divider-int-rc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xe2:m -U hfuse:w:0x99:m -U efuse:w:0xff:m 

fuses-no-divider-ext-osc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xff:m

fuses-with-divider-ext-osc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x7f:m

fuses-jtag-disable:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U hfuse:w:0xd9:m

EOF

# gpio.h
cat > "src/drivers/gpio.h" <<EOF
#ifndef GPIO_H_
#define GPIO_H_

/*
 * General purpose IO pins assignment and handling
 * ATmega1284 has 32 general purpose IO lines
 * Four 8bit ports (A, B, C, and D)
 */

#include <avr/io.h>
#include <stdint.h>

/*
 * Generic pin mapping
 */
#define _PA0            0U
#define _PA1            1U
#define _PA2            2U
#define _PA3            3U
#define _PA4            4U
#define _PA5            5U
#define _PA6            6U
#define _PA7            7U

#define _PB0            8U
#define _PB1            9U
#define _PB2            10U
#define _PB3            11U
#define _PB4            12U
#define _PB5            13U
#define _PB6            14U
#define _PB7            15U

#define _PC0            16U
#define _PC1            17U
#define _PC2            18U
#define _PC3            19U
#define _PC4            20U
#define _PC5            21U
#define _PC6            22U
#define _PC7            23U

#define _PD0            24U
#define _PD1            25U
#define _PD2            26U
#define _PD3            27U
#define _PD4            28U
#define _PD5            29U
#define _PD6            30U
#define _PD7            31U

/*
 * Hardware pin mapping
 */
#define _GPIO_01        _PB0
#define _GPIO_02        _PB1
#define _GPIO_03        _PB2
#define _GPIO_04        _PB3
#define _GPIO_05        _PB4
#define _GPIO_06        _PB5
#define _GPIO_07        _PB6
#define _GPIO_08        _PB7

#define _GPIO_14        _PD0
#define _GPIO_15        _PD1
#define _GPIO_16        _PD2
#define _GPIO_17        _PD3
#define _GPIO_18        _PD4
#define _GPIO_19        _PD5
#define _GPIO_20        _PD6
#define _GPIO_21        _PD7

#define _GPIO_22        _PC0
#define _GPIO_23        _PC1
#define _GPIO_24        _PC2
#define _GPIO_25        _PC3
#define _GPIO_26        _PC4
#define _GPIO_27        _PC5
#define _GPIO_28        _PC6
#define _GPIO_29        _PC7

#define _GPIO_33        _PA7
#define _GPIO_34        _PA6
#define _GPIO_35        _PA5
#define _GPIO_36        _PA4
#define _GPIO_37        _PA3
#define _GPIO_38        _PA2
#define _GPIO_39        _PA1
#define _GPIO_40        _PA0

/*
 * Addresses of DDRx, PORTx and PINx registers have the same offset and equals to 3.
 * It is useful for determining a real register address during a bit manipulation
 * 
 * PINA:0x00;  PINB:Ox03;  PINC:0x06;  PIND:0x09     -> offset = 3U
 * DDRA:0x01;  DDRB:0x04;  DDRC:0x07;  DDRD:0x0a     -> offset = 3U
 * PORTA:0x02; PORTB:0x05; PORTC:0x08; PORTD:0x0b    -> offset = 3U
 * 
 * Port A will be a starting point for determining adresses of direction, port, and pin registers for other ports (B, C, and D)
 */
#define _INIT_PIN_ADDRESS   ((volatile uint8_t*)&PINA)
#define _INIT_DDR_ADDRESS   ((volatile uint8_t*)&DDRA)
#define _INIT_PORT_ADDRESS  ((volatile uint8_t*)&PORTA)
#define _SFR_OFFSET         (3U)

/*
 * The main idea is that every value from generic pin map table represents two values: 
 * - pin number (0b00000111 a.k.a 7U mask); 
 * - port number (0b00011000 a.k.a. 3U << 3U, or 3U << GPIO_PORT_OFFSET).
 * 
 * Port number * SFR_OFFSET gives offset for determining the real register address. 
 * It depends on initial DDR, PORT, and PIN addresses.
 */
#define _GPIO_PORT_OFFSET       (3U)
#define _GPIO_PORT_MASK         (3U << _GPIO_PORT_OFFSET)
#define _GPIO_PIN_MASK          (7U)

/*
 * Macro for extracting the physical (hardware) bit value from generic pin value
 */
#define _GPIO_PIN_BIT(GPIO)     (1 << (GPIO & _GPIO_PIN_MASK))

/*
 * Macro for extracting the port number from the generic pin value
 */
#define _GPIO_PORT(GPIO)        ((GPIO & _GPIO_PORT_MASK) >> _GPIO_PORT_OFFSET)

#define _DDR_ADDRESS(GPIO)      (_INIT_DDR_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PORT_ADDRESS(GPIO)     (_INIT_PORT_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PIN_ADDRESS(GPIO)      (_INIT_PIN_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))

// High-level GPIO macros
#define gpio_set_output(GPIO)   (*_DDR_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define gpio_set_input(GPIO)    (*_DDR_ADDRESS(GPIO) &= (uint8_t) ~_GPIO_PIN_BIT(GPIO))
#define gpio_high(GPIO)         (*_PORT_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define gpio_low(GPIO)          (*_PORT_ADDRESS(GPIO) &= (uint8_t) ~_GPIO_PIN_BIT(GPIO))
#define gpio_toggle(GPIO)       (*_PIN_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define gpio_get_input(GPIO)    (*_PIN_ADDRESS(GPIO) & _GPIO_PIN_BIT(GPIO))

// Low-level inline assembly (sbi/cbi)
#define sbi_ddr(GPIO)   __asm__ volatile ("sbi %0, %1" :: "I" (_DDR_ADDRESS(GPIO) - __SFR_OFFSET), "I" (GPIO & _GPIO_PIN_MASK))
#define cbi_ddr(GPIO)   __asm__ volatile ("cbi %0, %1" :: "I" (_DDR_ADDRESS(GPIO) - __SFR_OFFSET), "I" (GPIO & _GPIO_PIN_MASK))
#define sbi_port(GPIO)  __asm__ volatile ("sbi %0, %1" :: "I" (_PORT_ADDRESS(GPIO) - __SFR_OFFSET), "I" (GPIO & _GPIO_PIN_MASK))
#define cbi_port(GPIO)  __asm__ volatile ("cbi %0, %1" :: "I" (_PORT_ADDRESS(GPIO) - __SFR_OFFSET), "I" (GPIO & _GPIO_PIN_MASK))
#define sbi_pin(GPIO)   __asm__ volatile ("sbi %0, %1" :: "I" (_PIN_ADDRESS(GPIO) - __SFR_OFFSET), "I" (GPIO & _GPIO_PIN_MASK))

#endif /* GPIO_H_ */
EOF

# README.md
cat > "README.md" <<EOF
### Topic
EOF