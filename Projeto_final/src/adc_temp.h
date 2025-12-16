#ifndef ADC_TEMP_H
#define ADC_TEMP_H

void adc_temp_init(void);

void adc_temp_read(void);

float adc_get_raw_internal(void);

void adc_thread_entry(void);

#endif