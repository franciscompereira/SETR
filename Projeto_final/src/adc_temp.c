#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>
#include "adc_temp.h"
#include "database.h"

#define ADC_PERIOD_MS 1000

LOG_MODULE_REGISTER(ADC_Module, LOG_LEVEL_INF);

K_TIMER_DEFINE(adc_timer, NULL, NULL); // Drift-free, hardware-backed timing

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0);

static int16_t buf; 
static struct adc_sequence sequence = {
    .buffer = &buf,
    .buffer_size = sizeof(buf),

};

static float shared_raw_value = 0.0f; // Local variable to be filtered (no need to be stored in the DB)

// Local getter function
float adc_get_raw_internal(void) {
    return shared_raw_value;
}

void adc_temp_init(void) // ADC Initialization
{
    if (!adc_is_ready_dt(&adc_channel))
    {
        LOG_INF("ADC controller not ready");
    }

    int error = adc_channel_setup_dt(&adc_channel);
    if (error < 0)
    {
        LOG_INF("Could not setup channel (%d)", error);
    }

    error = adc_sequence_init_dt(&adc_channel, &sequence);
    if (error < 0) {
        LOG_INF("Error: Could not init sequence (%d)\n", error);
    }
}

void adc_thread_entry(void) {
    
    adc_temp_init();

    k_timer_start(&adc_timer, K_MSEC(ADC_PERIOD_MS), K_MSEC(ADC_PERIOD_MS));

    while (1) {
        k_timer_status_sync(&adc_timer);

        int err = adc_read(adc_channel.dev, &sequence);
        if (err == 0) {
            
            int32_t val_mv = buf; // 
            adc_raw_to_millivolts_dt(&adc_channel, &val_mv);
            float temp = (val_mv - 500) / 10.0f;

            shared_raw_value = temp;
            k_sem_give(&adc_data_sem); 
        } else {
            LOG_INF("ADC Read Error: %d\n", err);
        }
    }
}


