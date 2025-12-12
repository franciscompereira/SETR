#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "database.h" 

// Hardware Aliases

#define SLEEP_TIME_MS 1000
#define DEBOUNCE_MS 200

#define BTN_ENABLE  DT_ALIAS(sw0)
#define BTN_INC     DT_ALIAS(sw1)
#define BTN_DEC     DT_ALIAS(sw3)   //definição dos diferentes botões

#define LED_STATUS  DT_ALIAS(led0)
#define LED_NORM    DT_ALIAS(led1)
#define LED_LOW     DT_ALIAS(led2)
#define LED_HIGH    DT_ALIAS(led3)      //definição dos diferentes leds

static const struct gpio_dt_spec btn_enable = GPIO_DT_SPEC_GET(BTN_ENABLE, gpios);
static const struct gpio_dt_spec btn_inc    = GPIO_DT_SPEC_GET(BTN_INC, gpios);
static const struct gpio_dt_spec btn_dec    = GPIO_DT_SPEC_GET(BTN_DEC, gpios);

static const struct gpio_dt_spec led_status = GPIO_DT_SPEC_GET(LED_STATUS, gpios);
static const struct gpio_dt_spec led_norm   = GPIO_DT_SPEC_GET(LED_NORM, gpios);
static const struct gpio_dt_spec led_low    = GPIO_DT_SPEC_GET(LED_LOW, gpios);
static const struct gpio_dt_spec led_high   = GPIO_DT_SPEC_GET(LED_HIGH, gpios);

static struct gpio_callback data_enable, data_inc, data_dec;

//debounce variables
static int last_time_enable = 0;
static int last_time_inc = 0;
static int last_time_dec = 0;

void button_enable_handler() //função que trata o botão de enable
{
    int now = k_uptime_get();
    int time_passed = now - last_time_enable;

    if (time_passed < DEBOUNCE_MS) {
        return; 
    } 
    else {
        last_time_enable = now;
    
        bool current_state = db_read_system_enable();
        db_write_system_enable(!current_state);
        gpio_pin_set_dt(&led_status, (int)(!current_state)); // led update
    }
}

void button_inc_handler()  //função que trata o botão de incremento
{ 
    int now = k_uptime_get();
    int time_passed = now - last_time_inc;

    if (time_passed < DEBOUNCE_MS) 
    {
        return;

    } else{
        last_time_inc = now;

        if (db_read_system_enable()) 
        {
        float val = db_read_target_temp();
        db_write_target_temp(val + 1.0f);
        }
    }
}

void button_dec_handler() //função que trata o botão de decremento
{
    int now = k_uptime_get();
    int time_passed = now - last_time_dec;
    if (time_passed < DEBOUNCE_MS) 
    {
        return;

    } else{
        last_time_dec = now;

    if (db_read_system_enable())
    {
        float val = db_read_target_temp();
        db_write_target_temp(val - 1.0f);
    }
    }
}

int ui_init(void)   //inicialização do hardware
{
    
    if (!gpio_is_ready_dt(&btn_enable)) return -1;      

    gpio_pin_configure_dt(&btn_enable, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&btn_enable, GPIO_INT_EDGE_TO_ACTIVE);     //configurar botão On/Off
    gpio_pin_configure_dt(&btn_inc, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&btn_inc, GPIO_INT_EDGE_TO_ACTIVE);         //Configurar botão de incremento
    gpio_pin_configure_dt(&btn_dec, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&btn_dec, GPIO_INT_EDGE_TO_ACTIVE);         //Configurar botão para decrementar

    gpio_pin_configure_dt(&led_status, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led_norm,   GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led_low,    GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led_high,   GPIO_OUTPUT_INACTIVE);           //Configuração dos LEDs

    gpio_init_callback(&data_enable, button_enable_handler, BIT(btn_enable.pin));        //Associa uma função ao premir do botão
    gpio_add_callback(btn_enable.port, &data_enable);
    gpio_init_callback(&data_inc, button_inc_handler, BIT(btn_inc.pin)); 
    gpio_add_callback(btn_inc.port, &data_inc);
    gpio_init_callback(&data_dec, button_dec_handler, BIT(btn_dec.pin));
    gpio_add_callback(btn_dec.port, &data_dec);

    return 0;
}

//acender e apagar leds
void ui_led_thread_entry() 
{  
    if (ui_init() != 0)
    {
        printk("Error: UI Init Failed!\n");
    }  

    int64_t next_run_time = k_uptime_get();

    while (1)
    {
        next_run_time += 1000;

        if (!db_read_system_enable()) {
            gpio_pin_set_dt(&led_norm, 0);
            gpio_pin_set_dt(&led_low, 0);
            gpio_pin_set_dt(&led_high, 0);
        } else {
            float diff = db_read_target_temp() - db_read_current_temp();

            if (diff > 5) //baixas temperaturas
            {       
                gpio_pin_set_dt(&led_low, 1);
                gpio_pin_set_dt(&led_norm, 0);
                gpio_pin_set_dt(&led_high, 0);
            } 
            else if (diff < -5) //altas temperaturas
            { 
                gpio_pin_set_dt(&led_low, 0);
                gpio_pin_set_dt(&led_norm, 0);
                gpio_pin_set_dt(&led_high, 1);
            } 
            else 
            {                
                gpio_pin_set_dt(&led_low, 0);
                gpio_pin_set_dt(&led_norm, 1);
                gpio_pin_set_dt(&led_high, 0);
            }
        }
        int remaining = next_run_time - k_uptime_get();
        if (remaining > 0) k_msleep(remaining);    
    }
}

//K_THREAD_DEFINE(ui_led_tid, 1024, ui_led_thread_entry, NULL, NULL, NULL, 4, 0, 0);