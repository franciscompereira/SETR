#ifndef ADC_TEMP_H
#define ADC_TEMP_H

/**
 * @brief Inicializa a ADC
 * @return 0 on success.
 */
void adc_temp_init(void);

/**
 * @brief Read the sensor voltage and convert to Celsius.
 * @return Temperature as a double (e.g., 25.5).
 */
void adc_temp_read(void);

#endif