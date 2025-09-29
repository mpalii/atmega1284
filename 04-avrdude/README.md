### 🖥️ USBasp

As a programmer I will use **USBasp** — a USB programmer for Atmel AVR controllers (see [usbasp official page](https://www.fischl.de/usbasp/)).  

After connecting the programmer to a USB port, check if the device is detected:  
```bash
lsusb
```

You should see something like:  
```
Bus XXX Device YYY: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb
```

⚠️ **Note:** The `vendorId:productId` pair must be **16c0:05dc**.  

---

### 📦 AVRDUDE (AVR Downloader-Uploader)

To install AVRDUDE:  
```bash
sudo apt install avrdude
```

To check connection with the AVR controller:  
```bash
avrdude -c usbasp -p m1284
```
Run it twice to make sure there are no communication issues.  

Additional options:  
- Bitclock:  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz
  ```
- Verbose output:  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz -v
  ```
- Maximum verbose:  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz -vvvvv
  ```

---

#### 📥 Dumping memory sections

```bash
avrdude -c usbasp -p m1284 -B 32kHz -vvv -U eeprom:r:eeprom_dump
avrdude -c usbasp -p m1284 -B 32kHz -vvv -U flash:r:flash_dump   # [bug report](http://savannah.nongnu.org/bugs/?44717)
avrdude -c usbasp -p m1284 -B 32kHz -vvvv -U flash:r:flash_dump
avrdude -c usbasp -p m1284 -B 32kHz -v -U lfuse:r:lfuse_dump
avrdude -c usbasp -p m1284 -B 32kHz -v -U hfuse:r:hfuse_dump
avrdude -c usbasp -p m1284 -B 32kHz -v -U efuse:r:efuse_dump
avrdude -c usbasp -p m1284 -B 32kHz -v -U lock:r:lock_dump
avrdude -c usbasp -p m1284 -B 32kHz -v -U signature:r:signature_dump
avrdude -c usbasp -p m1284 -B 32kHz -v -U calibration:r:calibration_dump
```

---

#### 📂 Different file formats

- Raw:  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:r
  ```
- Intel HEX ([ref](https://en.wikipedia.org/wiki/Intel_HEX)):  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:i
  ```
- Motorola SREC ([ref](https://en.wikipedia.org/wiki/SREC_(file_format))):  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:s
  ```
- Decimal, hex, binary:  
  ```bash
  avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:d
  avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:h
  avrdude -c usbasp -p m1284 -B 32kHz -v -U eeprom:r:eeprom_dump:b
  ```

---

### 🗑️ Remove AVRDUDE manually installed from sources

```bash
cd avrdude/build_linux
cat install_manifest.txt
xargs sudo rm -f < install_manifest.txt
which avrdude
```

---

### 🔗 See also

- [What does 'USBasp' stand for?](https://www.avrfreaks.net/s/topic/a5C3l000000UaMAEA0/t153548)  
- [AVRDUDE - AVR Downloader/Uploader (old)](https://www.nongnu.org/avrdude/)  
- [AVRDUDE Online Documentation](https://avrdudes.github.io/avrdude/)  
- [AVRDUDE GitHub repository](https://github.com/avrdudes/avrdude)  
- [AVRDUDE wiki](https://github.com/avrdudes/avrdude/wiki)  
- [8. AVR memories (datasheet)](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1184896)  
- [27. Memory programming (datasheet)](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1182132)  
- [14.2.2 Toggling the pin](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1057978)  
- [AVR® Instruction Set Manual](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [7.2.1 megaAVR® Devices](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e48916)  
- [SBRS – Skip if Bit in Register is Set](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e41641)  
- [CLR – Clear Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf#_OPENTOPIC_TOC_PROCESSING_d2079e23131)  
- [SBI – Set Bit in I/O Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/ReferenceManuals/AVR-InstructionSet-Manual-DS40002198.pdf)  
- [AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)  
- [What is the difference between /opt and /usr/local?](https://unix.stackexchange.com/questions/11544/what-is-the-difference-between-opt-and-usr-local)  
- [/usr/bin vs /usr/local/bin on Linux](https://unix.stackexchange.com/questions/8656/usr-bin-vs-usr-local-bin-on-linux)  
