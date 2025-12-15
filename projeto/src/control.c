#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "adc_temp.h"
#include "heater_PWM.h"
#include "pid.h"
#include "database.h"

LOG_MODULE_REGISTER(Control, LOG_LEVEL_INF);

// parametros PID
#define KP  12.0f
#define TI  250.0f
#define TD  2.0f

PID_Config my_pid;

#define PERIOD_in_MS 1000

void control_thread(void){
    
    pid_init(&my_pid, KP, TI, TD);

    float dt = 1.0f; // period: 1000ms

    int next_run_time = k_uptime_get() + PERIOD_in_MS;

    while (1)   //repetir continuamente
    {
        float temp = db_read_current_temp();
        float target = db_read_target_temp();
        bool on = db_read_system_enable();

        int power_command = 0;
        
        if (!on) {
            power_command = 0;
            pid_init(&my_pid, KP, TI, TD); 
        } else {
            power_command = pid_compute(&my_pid, target, temp, dt);
        }

        db_write_current_power(power_command);

        k_sem_give(&pwm_data_sem);
        
        int remaining = (int)(next_run_time - k_uptime_get()); // Sleep until exactly the next second mark
        if (remaining > 0) {
            k_msleep(remaining);
        }
        next_run_time += PERIOD_in_MS;
    }
    }
  