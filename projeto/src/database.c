#include "database.h"

// 1. PRIVATE DATA
static float  target_temp = 19.0f;
static float  current_temp = 0.0f;
static float  raw_temp = 0.0f;
static int    current_power = 0;
static bool   system_enable = false;

K_MUTEX_DEFINE(db_mutex);

void db_init(void) {
    // Mutex auto-initialization
}

// 3. ACCESS FUNCTIONS

void db_write_target_temp(float new_target) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    // Safety Limits
    if (new_target > 60.0f) new_target = 60.0f; 
    if (new_target < 20.0f) new_target = 20.0f;

    target_temp = new_target;
    k_mutex_unlock(&db_mutex);
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

void db_write_current_power(int new_power) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    current_power = new_power;
    k_mutex_unlock(&db_mutex);
}

int db_read_current_power(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    int val = current_power;
    k_mutex_unlock(&db_mutex);
    return val;
}

void db_write_system_enable(bool enable) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    system_enable = enable;
    k_mutex_unlock(&db_mutex);
}

bool db_read_system_enable(void) {
    k_mutex_lock(&db_mutex, K_FOREVER);
    bool val = system_enable;
    k_mutex_unlock(&db_mutex);
    return val;
}

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