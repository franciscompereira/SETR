#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "database.h"

LOG_MODULE_REGISTER(Display, LOG_LEVEL_INF); // Module Registration

K_TIMER_DEFINE(display_timer, NULL, NULL); // Drift-free, hardware-backed timing

void display_thread(void) {

    LOG_INF("THERMOSTAT STARTING");
    LOG_INF("System Ready. Press Button 1 to Start.");

    k_timer_start(&display_timer, K_MSEC(1000), K_MSEC(1000));

    // Local Printing Variables
    bool on;
    float target;
    float current;
    int8_t power;

    while (1) {
        k_timer_status_sync(&display_timer);

        // Reading Process
        on = db_read_system_enable();
        target = db_read_target_temp();
        current = db_read_current_temp();
        power = db_read_current_power();

        if (!on) {
            LOG_INF("System: [OFF] (Standby)");
        } 
        else {
            const char *status_msg;
            float diff = target - current;

            if (diff > 5.0f)       status_msg = "[HEATING]";
            else if (diff < -5.0f) status_msg = "[COOLING]";
            else                   status_msg = "[STABLE]";

            LOG_INF("System: [ON] | TGT: %.1f C | CUR: %.1f C | PWR: %d%% | %s", 
                   (double)target, (double)current, power, status_msg); // full dashboard line
        }
}
}