mkdir target
avr-gcc -mmcu=atmega1284 -Os -Wall -o ./target/firmware.elf ./src/main.c
