#ifndef heater_PWM_H
#define heater_PWM_H

#include <stdint.h>

/**
 * @brief Initializes the heater PWM.
 * @return 0 on success.
 */
int heater_init(void);

/**
 * @brief Sets the heater power.
 * @param intensity Percentage (0 to 100).
 */
void heater_set_intensity(uint8_t intensity);

#endif