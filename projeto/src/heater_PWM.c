#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>
#include "heater_PWM.h"

#define FREQ_OPERATION 500

LOG_MODULE_REGISTER(Heater_Module, LOG_LEVEL_INF);

static const struct pwm_dt_spec heater_dev = PWM_DT_SPEC_GET(DT_ALIAS(heater));

int heater_init(void) //inicialização do heater
{
    if (!pwm_is_ready_dt(&heater_dev)) {
        printk("Error: PWM device %s is not ready", heater_dev.dev->name);
        return -1;
    }
    
    // Safety: Start OFF
    heater_set_intensity(0);
    printk("Heater Initialized");
    return 0;
}

void heater_set_intensity(uint8_t intensity) {  
  
    if (intensity > 100) intensity = 100;
   
    uint32_t pulse_ns = (intensity * heater_dev.period) / 100;

    int err = pwm_set_pulse_dt(&heater_dev, pulse_ns);
    if (err) {
        printk("PWM set failed: %d", err);
    }
}

