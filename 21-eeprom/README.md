### EEPROM  

- To read the EEPROM section memory and create a dump as a raw binary 'eepromdump' file:  
`avrdude -c avrispmkII -p atmega1284 -U eeprom:r:eepromdump`  

- To check the content:  
`hexdump - C eepromdump`  
`xxd eepromdump`  

- To read the EEPROM section memory and create a dump as an intel format file 'eepromdump':  
`avrdude -c avrispmkII -p atmega1284 -U eeprom:r:eepromdump:i`   

- To write the raw data to EEPROM section memory:  
`avrdude -c avrispmkII -p atmega1284 -U eeprom:w:eepromdump:r`  

- Use 'EESAVE' bit in the 'Fuse High' byte to prevent memory erase through the chip erase  

---

### See also:   

- [EEPROM](https://en.wikipedia.org/wiki/EEPROM)  
- [Section 8.4 "EEPROM Data Memory"](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1448682)  
- [Section 8.6.1 EEARH and EEARL – The EEPROM Address Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1446879)  
- [Section 8.6.2 EEDR – The EEPROM Data Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1447057)  
- [Section 8.6.3 EECR – The EEPROM Control Register](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1447147)  
