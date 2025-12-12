#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "database.h"

#define DISPLAY_PERIOD_MS 1000
#define STACK_SIZE 2048  
#define PRIORITY 3   //menor prioridade

void display_thread(void) {

    printk("THERMOSTAT STARTING\n");
    printk("System Ready. Press Button 1 to Start.\n");

    int next_run_time = k_uptime_get();

    bool on;
    float target;
    float current;
    int power;

    while (1) {
        
        next_run_time += DISPLAY_PERIOD_MS; // 2. TIMING: Schedule next wake-up

        // read data safely
        on = db_read_system_enable();
        target = db_read_target_temp();
        current = db_read_current_temp();
        power = db_read_current_power();

        // PRINT DASHBOARD
        printk("System: [%s] ", on ? " ON" : "OFF");

        if (!on) {
            printk("(Standby)\n");
        } else {
            printk("| TGT: %.1f C | CUR: %.1f C | PWR: %d%%", 
                   (double)target, (double)current, power);

            float diff = target - current;
            if (diff > 5.0f) printk(" | [HEATING]\n");
            else if (diff < -5.0f) printk(" | [COOLING]\n");
            else printk(" | [STABLE]\n");
        }

        int remaining = next_run_time - k_uptime_get();
        if (remaining > 0) {
            k_msleep(remaining);
        }
    }
}

//K_THREAD_DEFINE(display_tid, STACK_SIZE, display_thread, NULL, NULL, NULL, PRIORITY, 0, 0);