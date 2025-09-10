### 📍 Pin State

Great — the first contact is established.  
Now it's time to take a multimeter and examine the voltage at the microcontroller pins.  
Before measuring, return the supply voltage to **5 V**.

After performing the measurements, record the obtained values in the table (*pin_voltage.ods*).

---

⚡ **Observation:**  
Most of the pins (Port **A**, **B**, **D**, and partially **C**) show a voltage in the range of **0.8–1.4 V**, which indicates that the pin is in a **high-impedance (High-Z) state** — in other words, the pin is "floating".  

To confirm the High-Z state of such pins, simply pull any of them down to **GND** (the negative terminal of the power source) and check the voltage again. The expected value should then be **0V**.

---

🔎 **Exception:**  
Pins **PC2**, **PC3**, **PC4**, and **PC5** behave differently.  
A voltmeter shows a **high potential** (very close to the supply voltage).  

This is explained in the datasheet:  
- [**25.8.1 MCUCR – MCU Control Register**](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1435790)  
- [**14.3.3 Alternate Functions of Port C**](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1059010)

By default, the **JTAG interface** is enabled, and pins **PC2–PC5** are used for JTAG functions in alternate mode.  

---

📊 **Pin Voltage Measurements**

| Port / Pin       | Measured Voltage | Expected State         |
|------------------|------------------|------------------------|
| PA0              | ~0.8–1.4 V       | High-Z (floating)      |
| PA1              | ~0.8–1.4 V       | High-Z (floating)      |
| PA2              | ~0.8–1.4 V       | High-Z (floating)      |
| PA3              | ~0.8–1.4 V       | High-Z (floating)      |
| PA4              | ~0.8–1.4 V       | High-Z (floating)      |
| PA5              | ~0.8–1.4 V       | High-Z (floating)      |
| PA6              | ~0.8–1.4 V       | High-Z (floating)      |
| PA7              | ~0.8–1.4 V       | High-Z (floating)      |
| PB0              | ~0.8–1.4 V       | High-Z (floating)      |
| PB1              | ~0.8–1.4 V       | High-Z (floating)      |
| PB2              | ~0.8–1.4 V       | High-Z (floating)      |
| PB3              | ~0.8–1.4 V       | High-Z (floating)      |
| PB4              | ~0.8–1.4 V       | High-Z (floating)      |
| PB5              | ~0.8–1.4 V       | High-Z (floating)      |
| PB6              | ~0.8–1.4 V       | High-Z (floating)      |
| PB7              | ~0.8–1.4 V       | High-Z (floating)      |
| PC0              | ~0.8–1.4 V       | High-Z (floating)      |
| PC1              | ~0.8–1.4 V       | High-Z (floating)      |
| **PC2**          | ~5 V             | JTAG active (driven)   |
| **PC3**          | ~5 V             | JTAG active (driven)   |
| **PC4**          | ~5 V             | JTAG active (driven)   |
| **PC5**          | ~5 V             | JTAG active (driven)   |
| PC6              | ~0.8–1.4 V       | High-Z (floating)      |
| PC7              | ~0.8–1.4 V       | High-Z (floating)      |
| PD0              | ~0.8–1.4 V       | High-Z (floating)      |
| PD1              | ~0.8–1.4 V       | High-Z (floating)      |
| PD2              | ~0.8–1.4 V       | High-Z (floating)      |
| PD3              | ~0.8–1.4 V       | High-Z (floating)      |
| PD4              | ~0.8–1.4 V       | High-Z (floating)      |
| PD5              | ~0.8–1.4 V       | High-Z (floating)      |
| PD6              | ~0.8–1.4 V       | High-Z (floating)      |
| PD7              | ~0.8–1.4 V       | High-Z (floating)      |
