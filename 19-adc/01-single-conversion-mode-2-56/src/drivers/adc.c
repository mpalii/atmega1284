#include "adc.h"
#include <avr/io.h>

void init_adc(void)
{
    // ADC Enable 
    ADCSRA |= _BV(ADEN); 
    // Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz)
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    // Internal 2.56V Voltage Reference with external capacitor at AREF pin
    ADMUX |= _BV(REFS1) | _BV(REFS0); 
    // Input Channel - ADC3
    ADMUX |= _BV(MUX1) | _BV(MUX0);
    // Digital Input Disable - ADC3
    DIDR0 |= _BV(ADC3D);
}

void adc_start_conversion(void)
{
    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}