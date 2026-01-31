#!/bin/bash
# C project initializer

if [ -e Makefile ] || [ -e src/main.c ]; then
    echo "Project already initialized"
    exit 1
fi

mkdir -p src

# main.c
cat > "src/main.c" <<EOF
/**
 * @author $(whoami)
 * @brief 
 * @version 1.0
 * @date $(date '+%Y-%m-%d')
 */


#include <stdio.h>

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
SOURCE       = ./src/main.c
DESTINATION  = firmware
DEVICE       = atmega1284
PROGRAMMER   = usbasp-clone

default: build

build: clean 
	@mkdir target
	@avr-gcc -mmcu=$(DEVICE) -Os -Wall -Wextra -Wconversion -o ./target/$(DESTINATION).elf $(SOURCE)
	@avr-objcopy --input-target elf32-avr --output-target ihex --verbose ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

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
	@avr-objdump -d ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@avr-size --format=AVR --mcu=$(DEVICE) ./target/$(DESTINATION).elf 

fuses-default:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xff:m 

fuses-no-divider-int-rc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xe2:m

fuses-no-divider-ext-osc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xff:m

fuses-with-divider-ext-osc:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x7f:m

EOF


