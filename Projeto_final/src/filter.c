#include <zephyr/kernel.h>
#include "filter.h"
#include "adc_temp.h"
#include "database.h"

void filter_thread_entry(void) {
    
    static float prev_temp = 0.0f;
    static bool first_run = true;

    while (1) {
/* SYNCHRONIZATION:
 * This thread is Event-Driven. It consumes 0% CPU while waiting.
 * It is effectively "clocked" by the ADC thread via semaphore.
 * ADC finishes -> Signals Semaphore -> Filter Wakes Up immediately.
 * This guarantees minimal latency between data acquisition and filtering.
 */
        // WAIT for the ADC to signal (Blocking!)
        k_sem_take(&adc_data_sem, K_FOREVER); // This thread sleeps here until ADC calls k_sem_give.

        float raw = adc_get_raw_internal(); // get raw data directly from ADC module

        float filtered;
        if (first_run) {
            filtered = raw;
            prev_temp = raw;
            first_run = false;
        } else {
            filtered = (raw + prev_temp) / 2.0f; // Moving Average
            prev_temp = raw;
        }

        db_write_current_temp(filtered); // PUBLISH to Database
    }
}