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

void heater_init(void) //inicialização do heater
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

    int64_t next_run = k_uptime_get();

    while(1) {
        k_sem_take(&pwm_data_sem, K_FOREVER);
        //next_run += 1000; 

        int power = db_read_current_power();
        set_pwm(power);

        //k_sleep(K_TIMEOUT_ABS_MS(next_run));
    }
}
