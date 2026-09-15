### System time and 7-segment display

A simple bare-metal project for the ATmega1284 demonstrating:

- Timer0 configured as a 1 ms system timebase using CTC mode
- Interrupt-driven software task scheduling
- Atomic access to shared data between ISR and main context
- Multiplexed control of a 4-digit common-cathode 7-segment display
- Generic GPIO abstraction with encoded port and pin information
- Display of elapsed system time in seconds
- AVR fuse configuration directly from C code
- Automatic header dependency tracking using GCC-generated `.d` files
- Makefile targets for building, flashing, fuse extraction, uploading, disassembly, size analysis, and flash dumping

---

### Build pipeline

```text
C source files
      │
      ▼
 Object files + dependency files
      │
      ▼
 firmware.elf
      ├───────────────► flash.hex
      │
      └───────────────► fuses.bin
                             │
                    ┌────────┼────────┐
                    ▼        ▼        ▼
                lfuse.hex hfuse.hex efuse.hex