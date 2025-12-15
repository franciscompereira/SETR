#include <zephyr/kernel.h>
#include <zephyr/logging/log.h> // 1. Include the Logging Header
#include "database.h"

/* 2. Register the Module (This sets the name appearing in the logs) */
LOG_MODULE_REGISTER(Display, LOG_LEVEL_INF);

#define DISPLAY_PERIOD_MS 1000

/* Remember: Threads must technically have 3 arguments */
void display_thread(void *p1, void *p2, void *p3) {

    /* 3. Use LOG_INF instead of printk */
    LOG_INF("THERMOSTAT STARTING");
    LOG_INF("System Ready. Press Button 1 to Start.");

    int next_run_time = k_uptime_get();

    bool on;
    float target;
    float current;
    int power;

    while (1) {
        next_run_time += DISPLAY_PERIOD_MS;

        on = db_read_system_enable();
        target = db_read_target_temp();
        current = db_read_current_temp();
        power = db_read_current_power();

        /* 4. Logic Change: Calculate the status string FIRST */
        if (!on) {
            // Print the full line at once
            LOG_INF("System: [OFF] (Standby)");
        } 
        else {
            const char *status_msg;
            float diff = target - current;

            if (diff > 5.0f)       status_msg = "[HEATING]";
            else if (diff < -5.0f) status_msg = "[COOLING]";
            else                   status_msg = "[STABLE]";

            /* 5. Print the full dashboard line in one go */
            /* Note: We use one big formatted string to avoid multiple log lines */
            LOG_INF("System: [ON] | TGT: %.1f C | CUR: %.1f C | PWR: %d%% | %s", 
                   (double)target, (double)current, power, status_msg);
        }

        int remaining = next_run_time - k_uptime_get();
        if (remaining > 0) {
            k_msleep(remaining);
        }
    }
}