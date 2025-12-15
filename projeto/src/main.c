#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "database.h"
#include "adc_temp.h"
#include "control.h"
#include "display_uart.h"
#include "UI.h"
#include "heater_PWM.h"
#include "filter.h"

#define DISPLAY_STACK 2048
#define STACK 1024

#define ADC_PRIORITY     1 
#define FILTER_PRIORITY  2 
#define CONTROL_PRIORITY 3 
#define PWM_PRIORITY     3 
#define LED_PRIORITY     4 
#define DISPLAY_PRIORITY 5

K_THREAD_DEFINE(adc_tid, STACK, adc_thread_entry, NULL, NULL, NULL, ADC_PRIORITY, 0, 0);
K_THREAD_DEFINE(filter_tid, STACK,  filter_thread_entry, NULL, NULL, NULL, FILTER_PRIORITY, 0, 0);
K_THREAD_DEFINE(control_tid, STACK,  control_thread, NULL, NULL, NULL, CONTROL_PRIORITY, 0, 0);
K_THREAD_DEFINE(pwm_tid, STACK,  pwm_thread_entry, NULL, NULL, NULL, PWM_PRIORITY, 0, 0);
K_THREAD_DEFINE(led_tid, STACK,  ui_led_thread_entry, NULL, NULL, NULL, LED_PRIORITY, 0, 0);
K_THREAD_DEFINE(disp_tid, DISPLAY_STACK, display_thread, NULL, NULL, NULL, DISPLAY_PRIORITY, 0, 0);

int main(void) 
{
    db_init();
    
    return 0;
}