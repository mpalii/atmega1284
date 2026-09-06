# Makefile
DESTINATION  = firmware
DEVICE       = atmega1284
PROGRAMMER   = avrispmkII

# Source files
SOURCES = 									\
    src/main.c 								\
	src/drivers/seven_segment.c				\

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

