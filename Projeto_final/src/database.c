#include "database.h"

// 1. PRIVATE DATA
static volatile float  target_temp = 19.0f;
static float  current_temp = 0.0f;
//static float  raw_temp = 0.0f;  // former test
static int8_t    current_power = 0;
static volatile bool   system_enable = false;

// Semaphore Definition (they start locked)
K_SEM_DEFINE(adc_data_sem, 0, 1); 
K_SEM_DEFINE(pwm_data_sem, 0, 1);

K_MUTEX_DEFINE(db_mutex);

void db_init(void) {
    // Mutex auto-initialization
}

// ACCESS FUNCTIONS (no mutex needed in volatile variables)

/* Mutex Removed for ISR Safety
target_temp is written by an Interrupt Service Routine (ISR) via buttons.
ISRs cannot wait for mutexes. Therefore, the variable is declared 'volatile'
to prevent compiler caching which avoids race conditions without locking.
 */

void db_write_target_temp(float new_target) {
    //k_mutex_lock(&db_mutex, K_FOREVER);

    // Safety Limits
    if (new_target > 60.0f) new_target = 60.0f; 
    if (new_target < 20.0f) new_target = 20.0f;

    target_temp = new_target;
    //k_mutex_unlock(&db_mutex);
}

float db_read_target_temp(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    float val = target_temp;
    k_mutex_unlock(&db_mutex);
    return val;
}

void db_write_current_temp(float new_temp) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    current_temp = new_temp;
    k_mutex_unlock(&db_mutex);
}

float db_read_current_temp(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    float val = current_temp;
    k_mutex_unlock(&db_mutex);
    return val;
}

void db_write_current_power(int8_t new_power) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    current_power = new_power;
    k_mutex_unlock(&db_mutex);
}

int8_t db_read_current_power(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    int8_t val = current_power;
    k_mutex_unlock(&db_mutex);
    return val;
}

void db_write_system_enable(bool enable) {
    //k_mutex_lock(&db_mutex, K_FOREVER);
    system_enable = enable;
    //k_mutex_unlock(&db_mutex);
}

bool db_read_system_enable(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    bool val = system_enable;
    k_mutex_unlock(&db_mutex);
    return val;
}

/*  no longer used (previous test )

void db_write_raw_temp(float val) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    raw_temp = val;
    k_mutex_unlock(&db_mutex);
}

float db_read_raw_temp(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    float val = raw_temp;
    k_mutex_unlock(&db_mutex);
    return val;
}
*/