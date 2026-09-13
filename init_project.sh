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
# ==============================================================
# Colored output
# ==============================================================
GREEN  = \033[1;32m
YELLOW = \033[1;33m
RED    = \033[1;31m
RESET  = \033[0m

# ==============================================================
# Project configuration
# ==============================================================
DEVICE      = atmega1284
PROGRAMMER  = avrispmkII
TARGET_DIR  = target
TARGET_NAME = firmware

# ==============================================================
# Tools
# ==============================================================
CC      = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size
AVRDUDE = avrdude

# ==============================================================
# Compiler flags
# ==============================================================
CFLAGS = \
	-mmcu=$(DEVICE) \
	-Os \
	-Wall \
	-Wextra \
	-Wconversion \
	-Wsign-conversion \
	-Woverflow

# ==============================================================
# objcopy flags
# ==============================================================
HEXFLAGS = \
	--input-target=elf32-avr \
	--output-target=ihex \
	--only-section=.text \
	--only-section=.data

FUSEFLAGS = \
	--input-target=elf32-avr \
	--output-target=binary \
	--only-section=.fuse 

# ==============================================================
# Source files
# ==============================================================
SOURCES = \
	src/main.c	\
	src/drivers/fuses.c

OBJECTS = $(patsubst src/%.c,$(TARGET_DIR)/%.o,$(SOURCES))

ELF = $(TARGET_DIR)/$(TARGET_NAME).elf
HEX = $(TARGET_DIR)/flash.hex

# ==============================================================
# Default target
# ==============================================================
.PHONY: default build clean check erase flash dump disasm size \
        fuses fuses-upload

default: build

# ==============================================================
# Build
# ==============================================================
build: $(HEX)
	@echo "$(GREEN)✔ Build finished$(RESET)"

# ==============================================================
# Linking
# ==============================================================
$(ELF): $(OBJECTS)
	@echo "$(YELLOW)⧗ Linking...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^

# ==============================================================
# HEX generation
# ==============================================================
$(HEX): $(ELF)
	@echo "$(YELLOW)⧗ Creating HEX...$(RESET)"
	@$(OBJCOPY) $(HEXFLAGS) $< $@

# ==============================================================
# Compilation
# ==============================================================
$(TARGET_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)⧗ Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# ==============================================================
# Fuse extraction
# ==============================================================
fuses: $(ELF)
	@echo "$(YELLOW)⧗ Extracting fuses...$(RESET)"

	@$(OBJCOPY) $(FUSEFLAGS) $< $(TARGET_DIR)/fuses.bin

	@dd if=$(TARGET_DIR)/fuses.bin \
		of=$(TARGET_DIR)/lfuse.bin \
		bs=1 count=1 skip=0 status=none

	@dd if=$(TARGET_DIR)/fuses.bin \
		of=$(TARGET_DIR)/hfuse.bin \
		bs=1 count=1 skip=1 status=none

	@dd if=$(TARGET_DIR)/fuses.bin \
		of=$(TARGET_DIR)/efuse.bin \
		bs=1 count=1 skip=2 status=none

	@$(OBJCOPY) -I binary -O ihex \
		$(TARGET_DIR)/lfuse.bin \
		$(TARGET_DIR)/lfuse.hex

	@$(OBJCOPY) -I binary -O ihex \
		$(TARGET_DIR)/hfuse.bin \
		$(TARGET_DIR)/hfuse.hex

	@$(OBJCOPY) -I binary -O ihex \
		$(TARGET_DIR)/efuse.bin \
		$(TARGET_DIR)/efuse.hex

	@echo -n "lfuse="
	@hexdump -v -e '1/1 "0x%02X\n"' $(TARGET_DIR)/lfuse.bin

	@echo -n "hfuse="
	@hexdump -v -e '1/1 "0x%02X\n"' $(TARGET_DIR)/hfuse.bin

	@echo -n "efuse="
	@hexdump -v -e '1/1 "0x%02X\n"' $(TARGET_DIR)/efuse.bin

	@rm --force $(TARGET_DIR)/*.bin

	@echo "$(GREEN)✔ Fuse files created$(RESET)"

# ==============================================================
# Programming
# ==============================================================
check:
	@$(AVRDUDE) \
		-c $(PROGRAMMER) \
		-p $(DEVICE)

erase:
	@$(AVRDUDE) \
		-c $(PROGRAMMER) \
		-p $(DEVICE) \
		-e

flash: $(HEX)
	@echo "$(YELLOW)⧗ Uploading flash...$(RESET)"
	@$(AVRDUDE) \
		-c $(PROGRAMMER) \
		-p $(DEVICE) \
		-U flash:w:$(HEX):i

fuses-upload:
	@echo "$(YELLOW)⧗ Uploading fuses...$(RESET)"
	@$(AVRDUDE) \
		-c $(PROGRAMMER) \
		-p $(DEVICE) \
		-U lfuse:w:$(TARGET_DIR)/lfuse.hex:i \
		-U hfuse:w:$(TARGET_DIR)/hfuse.hex:i \
		-U efuse:w:$(TARGET_DIR)/efuse.hex:i

# ==============================================================
# Information / analysis
# ==============================================================
disasm: $(ELF)
	@$(OBJDUMP) --section-headers $(ELF)
	@$(OBJDUMP) --disassemble $(ELF)
	@$(OBJDUMP) --full-contents --section=.data $(ELF)

size: $(ELF)
	@$(SIZE) \
		--format=AVR \
		--mcu=$(DEVICE) \
		$(ELF)

dump:
	@$(AVRDUDE) \
		-c $(PROGRAMMER) \
		-p $(DEVICE) \
		-U flash:r:-:h

# ==============================================================
# Clean
# ==============================================================
clean:
	@rm --force --recursive --verbose $(TARGET_DIR)
	@echo "$(RED)✘ Clean finished$(RESET)"
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

# fuses.c
cat > "src/drivers/fuses.c" <<EOF
#include <avr/io.h>

/*
 * Fuses configuration default:
 * lfuse=0x62
 * hfuse=0x99
 * efuse=0xFF
 */

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
EOF


# README.md
cat > "README.md" <<EOF
### Topic
EOF