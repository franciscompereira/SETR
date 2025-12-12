#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>
#include "adc_temp.h"
#include "database.h"

LOG_MODULE_REGISTER(ADC_Module, LOG_LEVEL_INF);

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0);

static int16_t buf; 
static struct adc_sequence sequence = {
    .buffer = &buf,
    .buffer_size = sizeof(buf),

};

void adc_temp_init(void)    //inicialização da ADC
{
    if (!adc_is_ready_dt(&adc_channel))
    {
        printk("ADC controller not ready");
    }

    int error = adc_channel_setup_dt(&adc_channel);
    if (error < 0)
    {
        printk("Could not setup channel (%d)", error);
    }

    (void)adc_sequence_init_dt(&adc_channel, &sequence);
}

void adc_temp_read(void)  
{
    int error;
    int32_t val_mv;
    adc_temp_init();
    
    while(1)
    {
        error = adc_read(adc_channel.dev, &sequence);
        if (error < 0)
        {
            printk("ADC read failed (%d)", error);
            return;
        }

        val_mv = buf;
        adc_raw_to_millivolts_dt(&adc_channel, &val_mv);

        float temp = (val_mv - 500) / 10.0;
        db_write_raw_temp(temp);
        k_msleep(100);
    
    }
}

//K_THREAD_DEFINE(temperature_read, 1024, adc_temp_read, NULL, NULL, NULL, 1, 0, 0);