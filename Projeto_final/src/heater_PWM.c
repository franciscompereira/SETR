#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>
#include "heater_PWM.h"
#include "database.h"

LOG_MODULE_REGISTER(Heater_Module, LOG_LEVEL_INF);

static const struct pwm_dt_spec heater_dev = PWM_DT_SPEC_GET(DT_ALIAS(heater));

static void set_pwm(uint8_t intensity) {  
  
    if (intensity > 100) intensity = 100;
    uint32_t pulse_ns = (intensity * heater_dev.period) / 100;
    int err = pwm_set_pulse_dt(&heater_dev, pulse_ns);
    if (err) {
        printk("PWM set failed: %d", err);
    }
}

void heater_init(void) // Heater Initialization
{
    if (!pwm_is_ready_dt(&heater_dev)) {
        printk("Error: PWM device %s is not ready", heater_dev.dev->name);
        return;
    }

    set_pwm(0);
    printk("Heater Initialized (PWM)\n");
}

void pwm_thread_entry(void) {
    
    heater_init();
    set_pwm(0);

    while(1) {
        k_sem_take(&pwm_data_sem, K_FOREVER);

        int8_t power = db_read_current_power();
        set_pwm(power);
    }
}
