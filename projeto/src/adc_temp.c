#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>
#include "adc_temp.h"
#include "database.h"

#define ADC_PERIOD_MS 1000

LOG_MODULE_REGISTER(ADC_Module, LOG_LEVEL_INF);

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0);

static int16_t buf; 
static struct adc_sequence sequence = {
    .buffer = &buf,
    .buffer_size = sizeof(buf),

};

static float shared_raw_value = 0.0f;
//K_SEM_DEFINE(adc_data_sem, 0, 1);

float adc_get_raw_internal(void) {
    return shared_raw_value;
}

void adc_temp_init(void)    //inicialização da ADC
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
    int64_t next_run = k_uptime_get();

    while (1) {
        

        int err = adc_read(adc_channel.dev, &sequence);
        if (err == 0) {
            
            int32_t val_mv = buf;
            adc_raw_to_millivolts_dt(&adc_channel, &val_mv);
            float temp = (val_mv - 500) / 10.0f;

            shared_raw_value = temp;
            k_sem_give(&adc_data_sem); 
        } else {
            LOG_INF("ADC Read Error: %d\n", err);
        }
        int remaining = next_run - k_uptime_get();
        if (remaining > 0) {
            k_msleep(remaining);
        }
        next_run += ADC_PERIOD_MS; // 1 second period
    }
}


