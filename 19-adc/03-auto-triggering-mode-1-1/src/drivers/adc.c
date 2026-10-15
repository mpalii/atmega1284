#include "adc.h"

#include <avr/interrupt.h>
#include <util/atomic.h>

#include "gpio.h"

static volatile uint16_t conversion_result = 0;

ISR(ADC_vect)
{
    // profiling
    sbi_pin(LED);
    conversion_result = ADC;
}

#include <avr/io.h>

void init_adc(void)
{
    // Internal 1.1V Voltage Reference with external capacitor at AREF pin
    ADMUX |= _BV(REFS1); 
    // Input Channel - ADC3
    ADMUX |= _BV(MUX1) | _BV(MUX0);
    // Digital Input Disable - ADC3
    DIDR0 |= _BV(ADC3D);
    // Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz)
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    // ADC Interrupt Enable
    ADCSRA |= _BV(ADIE);
    // ADC Auto trigger enable
    ADCSRA |= _BV(ADATE);
    // Trigger source: Timer/Counter0 Compare Match A
    ADCSRB |= _BV(ADTS1) | _BV(ADTS0);
    // ADC Enable 
    ADCSRA |= _BV(ADEN); 
}

void adc_start_conversion(void)
{
    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}

uint16_t adc_get_conversion_result(void)
{
    uint16_t conversion_result_copy;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        conversion_result_copy = conversion_result;
    }
    return conversion_result_copy;
}