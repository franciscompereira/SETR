#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "adc_temp.h"
#include "heater_PWM.h"
#include "pid.h"
#include "database.h"

LOG_MODULE_REGISTER(Control, LOG_LEVEL_INF);

// PID Parameters
#define KP  20.0f  
#define TI  130.0f 
#define TD  1.0f   

PID_Config my_pid;

K_TIMER_DEFINE(control_timer, NULL, NULL); // Drift-free, hardware-backed timing

void control_thread(void){
    
    pid_init(&my_pid, KP, TI, TD);

    k_timer_start(&control_timer, K_MSEC(1000), K_MSEC(1000));

    float dt = 1.0f; // period: 1000ms

    while (1)
    {
        k_timer_status_sync(&control_timer);
        
        // Local Reading Variables 
        float temp = db_read_current_temp();
        float target = db_read_target_temp();
        bool on = db_read_system_enable();

        int8_t power_command = 0;
        
        if (!on) {
            power_command = 0;
            pid_init(&my_pid, KP, TI, TD); 
        } else {
            power_command = (int8_t)pid_compute(&my_pid, target, temp, dt); // PID math doing its job
        }

        db_write_current_power(power_command); // current state goes straight to the database

        k_sem_give(&pwm_data_sem);
    }
    }
  