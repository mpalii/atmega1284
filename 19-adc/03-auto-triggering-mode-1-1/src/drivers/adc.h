#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void init_adc(void);
void adc_start_conversion(void);
uint16_t adc_get_conversion_result(void);

#endif /* ADC_H_ */