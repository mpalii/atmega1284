#include "adc.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/atomic.h>

#include "gpio.h"

#define REFFERENCE_VOLTAGE_UV (1087000UL)
#define ADC_RESOLUTION (1024)
#define CONVERSION_RATIO (REFFERENCE_VOLTAGE_UV / ADC_RESOLUTION)
#define WINDOW_SIZE (512)

#define VOLTAGE_OFFSET (5)
#define RESULT_SHIFT   (2)

uint16_t calculation_window_buffer[WINDOW_SIZE] = { 0, };
static volatile uint32_t buffer_sum = 0;
static volatile uint16_t index = 0;

ISR(ADC_vect)
{
    // profiling
    sbi_pin(LED);
    
    buffer_sum -= calculation_window_buffer[index];
    calculation_window_buffer[index] = ADC;
    buffer_sum += calculation_window_buffer[index];

    if (++index > (WINDOW_SIZE - 1))
    {
        index = 0;
    }
}

void init_adc(void)
{
    // Internal 1.1V Voltage Reference with external capacitor at AREF pin
    ADMUX |= _BV(REFS1); 
    // Input Channel - ADC3
    ADMUX |= _BV(MUX1) | _BV(MUX0);
    // Digital Input Disable - ADC3
    DIDR0 |= _BV(ADC3D);
    // Trigger source: Timer/Counter0 Compare Match A
    ADCSRB |= _BV(ADTS1) | _BV(ADTS0);
    // Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz)
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    // ADC Interrupt Enable
    ADCSRA |= _BV(ADIE);
    // ADC Auto trigger enable
    ADCSRA |= _BV(ADATE);
    // ADC Enable 
    ADCSRA |= _BV(ADEN); 
    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}

uint16_t adc_get_conversion_result(void)
{
    uint32_t buffer_sum_copy;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        buffer_sum_copy = buffer_sum;
    }
    // return (uint16_t) (buffer_sum_copy / WINDOW_SIZE);
    uint16_t raw_voltage = (uint16_t) (((buffer_sum_copy / WINDOW_SIZE) * CONVERSION_RATIO) / 1000);
    uint16_t result = raw_voltage + VOLTAGE_OFFSET - RESULT_SHIFT;
    // range adjustment

    return result;
}
