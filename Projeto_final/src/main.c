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
#define LED_PRIORITY     5 
#define DISPLAY_PRIORITY 6

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

/* RAM used: 2.66% (6976 B / 256 kB)

THREAD: ADC Acquisition
>> AVG TIME = 90 us
>> MAX TIME = 123 us

THREAD: Filter Logic
>> AVG TIME = 6 us
>> MAX TIME = 31 us

THREAD: Control Logic
>> AVG TIME = 12 us
>> MAX TIME = 31 us

THREAD: PWM Actuation
>> AVG TIME = 14 us
>> MAX TIME = 31 us

THREAD: LEDs
>> AVG TIME = 6 us
>> MAX TIME = 31 us

THREAD: Display
>> AVG TIME = 16 us
>> MAX TIME = 31 us

*/
