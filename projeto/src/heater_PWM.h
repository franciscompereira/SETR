#ifndef heater_PWM_H
#define heater_PWM_H

#include <stdint.h>

//static void set_pwm(uint8_t intensity); helper function

void heater_init(void);

void pwm_thread_entry(void);

#endif