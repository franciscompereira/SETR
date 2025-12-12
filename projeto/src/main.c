#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "database.h"
#include "adc_temp.h"
#include "control.h"
#include "display_uart.h"
#include "UI.h"
#include "heater_PWM.h"

#define ADC_READ_STACK 1024
#define ADC_READ_PRIORITY 1

#define CONTROL_STACK 1024
#define CONTROL_PRIORITY 2

#define DISPLAY_STACK 2048
#define DISPLAY_PRIORITY 3

#define LED_STACK 1024
#define LED_PRIORITY 4

K_THREAD_DEFINE(temperature_read, ADC_READ_STACK, adc_temp_read, NULL, NULL, NULL, ADC_READ_PRIORITY, 0, 0);    //criar task de leitura de temperatura
K_THREAD_DEFINE(control_id, CONTROL_STACK, control_thread, NULL, NULL, NULL, CONTROL_PRIORITY, 0, 0);           //criar task de controlo
K_THREAD_DEFINE(display_tid, DISPLAY_STACK, display_thread, NULL, NULL, NULL, DISPLAY_PRIORITY, 0, 0);          //criar task de display
K_THREAD_DEFINE(ui_led_tid, LED_STACK, ui_led_thread_entry, NULL, NULL, NULL, LED_PRIORITY, 0, 0);

int main(void) 
{
    db_init();
    
    return 0;
}