#ifndef PID_H
#define PID_H

typedef struct {
    // Tuning Constants
    float Kp;
    float Ti;
    float Td;

    // Memory (State)
    float integral;
    float prev_error;
    
    // Safety Limits
    float out_min;
    float out_max;
} PID_Config;

void pid_init(PID_Config *pid, float Kp, float Ti, float Td);
int pid_compute(PID_Config *pid, float setpoint, float current_val, float dt);

#endif