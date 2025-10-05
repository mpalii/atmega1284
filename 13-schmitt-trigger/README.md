# Schmitt trigger

[30.7.9 Pin threshold and hysteresis](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.2093201)  
[14.2 Ports as General Digital I/O](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATmega164A_PA-324A_PA-644A_PA-1284_P_Data-Sheet-40002070B.pdf#G3.1339402)  
[Difference Between Digital Latch and Flip-Flop Circuits](https://www.electricaltechnology.org/2024/06/difference-between-latch-flip-flop.html) 
[The “Buffer” Gate](https://www.allaboutcircuits.com/textbook/digital/chpt-3/buffer-gate/)

TODO   
- tristate buffer  
- bidirectional tristate buffer  
- transmission gate (star?)  

[What is the difference between a tristate buffer and a transmission gate?](https://electronics.stackexchange.com/questions/692525/what-is-the-difference-between-a-tristate-buffer-and-a-transmission-gate)  


https://www.nationin.com/post/cmos-transmission-gate?srsltid=AfmBOopPHoOmWCf0OXBNlVbCMaUickfIUB-51H-9XsYkpUCyKUpS325r  

p-channel mosfet - with ring on gate (logical 0 - open)  
n-channel mosfet - witout ring on gate (logical 1 - open)  

https://eax.me/mosfet-cheet-sheet/  



FROM GPT???

🔹 1. n-канальный MOSFET (NMOS)
Источник (S) обычно сидит на «низу» (GND).
Чтобы открыть канал, на затвор (G) нужно подать положительное напряжение относительно истока (V_GS > V_TH).
Когда V_GS превышает порог (обычно 1–3 В для логических MOSFET, 2–4 В и выше для силовых), между стоком (D) и истоком появляется проводимость.
Чем выше V_GS, тем меньше сопротивление канала (R_DS(on)).

👉 Итого: NMOS открывается, если G выше S на величину больше порогового напряжения.

🔹 2. p-канальный MOSFET (PMOS)
Источник (S) обычно сидит на «верху» (VCC).
Чтобы открыть канал, нужно подать на затвор напряжение ниже источника (V_GS < –V_TH).
Например, если S = +5 В, то чтобы открыть транзистор, G нужно опустить, скажем, до +3 В или ниже (если порог 1–2 В).
Чем ниже G относительно S, тем сильнее он проводит.

👉 Итого: PMOS открывается, если G ниже S на величину больше порога.
