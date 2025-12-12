#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "adc_temp.h"
#include "heater_PWM.h"
#include "pid.h"
#include "database.h"

LOG_MODULE_REGISTER(Control, LOG_LEVEL_INF);

// parametros PID
#define KP  30.0f
#define TI  60.0f
#define TD  40.0f

PID_Config my_pid;

#define PERIOD_in_MS 1000

void control_thread(void) {
    
    heater_init();
    pid_init(&my_pid, KP, TI, TD);

    float dt = 1.0f; // period: 1000ms

    static float prev_temp = 0.0f;
    static bool first_run = true;

    int next_run_time = k_uptime_get() + PERIOD_in_MS;

    while (1)   //repetir continuamente
    {
        float raw_reading = db_read_raw_temp();
        float current_val = raw_reading;

        float filtered_temp;
        
        if (first_run) {
            filtered_temp = current_val;
            prev_temp = current_val;
            first_run = false;
        } else {
            filtered_temp = (current_val + prev_temp) / 2.0f; //average
            prev_temp = current_val; // Update previous for the next loop
        }

        db_write_current_temp(filtered_temp);
        
        bool enabled = db_read_system_enable();
        float target = db_read_target_temp();

        if (!enabled) {
            heater_set_intensity(0);
            db_write_current_power(0);
            pid_init(&my_pid, KP, TI, TD); // Reset Anti-windup
        }

        else {
            int power = pid_compute(&my_pid, target, filtered_temp, dt);
            heater_set_intensity(power);
            db_write_current_power(power);
        }
        
        int remaining = (int)(next_run_time - k_uptime_get()); // Sleep until exactly the next second mark
        if (remaining > 0) {
            k_msleep(remaining);
        }
        next_run_time += PERIOD_in_MS;
    }
    }

//K_THREAD_DEFINE(control_id, 1024, control_thread, NULL, NULL, NULL, 2, 0, 0);    