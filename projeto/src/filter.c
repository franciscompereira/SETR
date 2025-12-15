#include <zephyr/kernel.h>
#include "filter.h"
#include "adc_temp.h"
#include "database.h"

void filter_thread_entry(void) {
    
    static float prev_temp = 0.0f;
    static bool first_run = true;

    while (1) {
        // 1. WAIT for the ADC to signal (Blocking!)
        k_sem_take(&adc_data_sem, K_FOREVER); // This thread sleeps here until ADC calls k_sem_give.

        // 2. GET RAW DATA (Directly from ADC module)
        float raw = adc_get_raw_internal();

        // 3. FILTER (Moving Average)
        float filtered;
        if (first_run) {
            filtered = raw;
            prev_temp = raw;
            first_run = false;
        } else {
            filtered = (raw + prev_temp) / 2.0f;
            prev_temp = raw;
        }

        db_write_current_temp(filtered); // 4. PUBLISH to Database
    }
}