#include <zephyr/kernel.h>
#include "pid.h"

void pid_init(PID_Config *pid, float Kp, float Ti, float Td) // PID Initialization
{
    pid->Kp = Kp;
    pid->Ti = Ti;
    pid->Td = Td;
    
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
    
    // Output Limits (0% to 100% Power)
    pid->out_min = 0.0f;
    pid->out_max = 100.0f;
}

int pid_compute(PID_Config *pid, float setpoint, float current_val, float dt) {
    float error = setpoint - current_val;

    float P = pid->Kp * error; // Proportional Component

    pid->integral += error * dt; 
    float I = (pid->Kp / pid->Ti) * pid->integral; // Integrative Component

    float derivative = (error - pid->prev_error) / dt;
    float D = (pid->Kp * pid->Td) * derivative; // Derivative Component

    float output = P + I + D; // Total
    
    if (output > pid->out_max) {
        output = pid->out_max;
        if (error > 0) {
            pid->integral -= error * dt; 
        }
    } else if (output < pid->out_min) {
        output = pid->out_min;
        if (error < 0) {
            pid->integral -= error * dt;
        }
    }

    pid->prev_error = error; // Keep state

    return (int)output;
}