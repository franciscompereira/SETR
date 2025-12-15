#include <zephyr/kernel.h>
#include "pid.h"

void pid_init(PID_Config *pid, float Kp, float Ti, float Td) 
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

    float P = pid->Kp * error; // Componente proporcional

    pid->integral += error * dt; 
    float I = (pid->Kp / pid->Ti) * pid->integral; // Componente Integradora

    float derivative = (error - pid->prev_error) / dt;
    float D = (pid->Kp * pid->Td) * derivative; // Componente derivativa

    float output = P + I + D; // Total
    
    if (output > pid->out_max) {
        output = pid->out_max;
        /* Only stop growing if we are adding to the problem */
        if (error > 0) {
            pid->integral -= error * dt; 
        }
    } else if (output < pid->out_min) {
        output = pid->out_min;
        /* Only stop growing if we are adding to the problem */
        if (error < 0) {
            pid->integral -= error * dt;
        }
    }

    pid->prev_error = error; // Guardar estado

    return (int)output;
}

/* old version

 if (output > pid->out_max) {
        output = pid->out_max; // Estabelecer maximos 
        pid->integral -= error * dt; 
    } else if (output < pid->out_min) {
        output = pid->out_min;
        pid->integral -= error * dt;
    }

*/