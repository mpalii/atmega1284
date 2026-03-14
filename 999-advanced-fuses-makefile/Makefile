# ==============================================================
# Project configuration
# ==============================================================

DEVICE       = atmega1284
PROGRAMMER   = usbasp
SOURCE       = src/main.c
TARGET_DIR   = target
TARGET_NAME  = firmware

# ==============================================================
# Tools
# ==============================================================

CC       = avr-gcc
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump
SIZE     = avr-size
AVRDUDE  = avrdude

CFLAGS   = -mmcu=$(DEVICE) -Os -Wall -Wextra -Wconversion
HEXFLAGS = -j .text -j .data -O ihex
FUSEFLAGS = -j .fuse -O binary

# Colored output
GREEN=\033[1;32m
YELLOW=\033[1;33m
RED=\033[1;31m
RESET=\033[0m

# ==============================================================
# Targets
# ==============================================================

default: build

build: clean $(TARGET_DIR)/$(TARGET_NAME).elf $(TARGET_DIR)/flash.hex fuses
	@echo "$(GREEN)✔ Build finished$(RESET)"

$(TARGET_DIR)/$(TARGET_NAME).elf: $(SOURCE)
	@mkdir -p $(TARGET_DIR)
	@echo "$(YELLOW)⧗ Compiling...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $<

$(TARGET_DIR)/flash.hex: $(TARGET_DIR)/$(TARGET_NAME).elf
	@echo "$(YELLOW)⧗ Creating HEX...$(RESET)"
	@$(OBJCOPY) $(HEXFLAGS) $< $@

# ==============================================================
# Fuse extraction
# ==============================================================

fuses: $(TARGET_DIR)/$(TARGET_NAME).elf
	@echo "$(YELLOW)⧗ Extracting fuses...$(RESET)"
	@$(OBJCOPY) $(FUSEFLAGS) $< $(TARGET_DIR)/fuses.bin
	@dd if=$(TARGET_DIR)/fuses.bin of=$(TARGET_DIR)/lfuse.bin bs=1 count=1 skip=0 status=none
	@dd if=$(TARGET_DIR)/fuses.bin of=$(TARGET_DIR)/hfuse.bin bs=1 count=1 skip=1 status=none
	@dd if=$(TARGET_DIR)/fuses.bin of=$(TARGET_DIR)/efuse.bin bs=1 count=1 skip=2 status=none
	@$(OBJCOPY) -I binary -O ihex $(TARGET_DIR)/lfuse.bin $(TARGET_DIR)/lfuse.hex
	@$(OBJCOPY) -I binary -O ihex $(TARGET_DIR)/hfuse.bin $(TARGET_DIR)/hfuse.hex
	@$(OBJCOPY) -I binary -O ihex $(TARGET_DIR)/efuse.bin $(TARGET_DIR)/efuse.hex
	@echo "$(GREEN)✔ Fuse files created$(RESET)"
	@echo -n "lfuse="; hexdump -v -e '1/1 "0x%02X\n"' $(TARGET_DIR)/lfuse.bin
	@echo -n "hfuse="; hexdump -v -e '1/1 "0x%02X\n"' $(TARGET_DIR)/hfuse.bin
	@echo -n "efuse="; hexdump -v -e '1/1 "0x%02X\n"' $(TARGET_DIR)/efuse.bin
	@rm $(TARGET_DIR)/*.bin

# ==============================================================
# Programming
# ==============================================================

upload-flash:
	@echo "$(YELLOW)⧗ Uploading flash...$(RESET)"
	@$(AVRDUDE) -c $(PROGRAMMER) -p $(DEVICE) \
		-U flash:w:$(TARGET_DIR)/flash.hex:i

upload-fuses:
	@echo "$(YELLOW)⧗ Uploading fuses...$(RESET)"
	@$(AVRDUDE) -c $(PROGRAMMER) -p $(DEVICE) \
		-U lfuse:w:$(TARGET_DIR)/lfuse.hex:i \
		-U hfuse:w:$(TARGET_DIR)/hfuse.hex:i \
		-U efuse:w:$(TARGET_DIR)/efuse.hex:i

fuses-default:
	@$(AVRDUDE) -c $(PROGRAMMER) -p $(DEVICE) \
		-U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xFF:m

erease:
	@$(AVRDUDE) -c $(PROGRAMMER) -p $(DEVICE) -e

check:
	@$(AVRDUDE) -c $(PROGRAMMER) -p $(DEVICE)

# ==============================================================
# Tools & info
# ==============================================================

disasm:
	@$(OBJDUMP) -d $(TARGET_DIR)/$(TARGET_NAME).elf | less

size:
	@$(SIZE) --format=AVR --mcu=$(DEVICE) $(TARGET_DIR)/$(TARGET_NAME).elf

clean:
	@rm -rf $(TARGET_DIR)
	@echo "$(RED)✘ Clean finished$(RESET)"
