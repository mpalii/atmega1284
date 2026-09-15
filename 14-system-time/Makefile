# ==============================================================
# Colored output
# ==============================================================
GREEN  = \033[1;32m
YELLOW = \033[1;33m
RED    = \033[1;31m
RESET  = \033[0m

# ==============================================================
# Default goal
# ==============================================================
.DEFAULT_GOAL := default

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
	-Woverflow \
	-MMD \
	-MP

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
	src/task_manager.c \
	src/config/fuses.c \
	src/drivers/seven_segment.c \
	src/drivers/timer0.c

OBJECTS = $(patsubst src/%.c,$(TARGET_DIR)/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)
-include $(DEPENDS)

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

	@echo -n "lfuse="
	@hexdump -v -s 0 -n 1 -e '1/1 "0x%02X\n"' $(TARGET_DIR)/fuses.bin
	@echo -n "hfuse="
	@hexdump -v -s 1 -n 1 -e '1/1 "0x%02X\n"' $(TARGET_DIR)/fuses.bin
	@echo -n "efuse="
	@hexdump -v -s 2 -n 1 -e '1/1 "0x%02X\n"' $(TARGET_DIR)/fuses.bin

	@echo "$(GREEN)✔ Fuses file created$(RESET)"

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
	@if [ ! -f "$(TARGET_DIR)/fuses.bin" ]; then \
		echo "$(RED)✘ Error: fuses.bin not found$(RESET)"; \
		exit 1; \
	fi

	@echo "$(YELLOW)⧗ Uploading fuses...$(RESET)"

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
