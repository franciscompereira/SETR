#ifndef DATABASE_H
#define DATABASE_H

#include <zephyr/kernel.h>

// Initialize the database (mutex)
void db_init(void);

// WRITERS
void db_write_target_temp(float new_target);
void db_write_current_temp(float new_temp);
void db_write_current_power(int new_power);
void db_write_system_enable(bool enable);

// READERS
float db_read_target_temp(void);
float db_read_current_temp(void);
int   db_read_current_power(void);
bool  db_read_system_enable(void);

void db_write_raw_temp(float val);
float db_read_raw_temp(void);

#endif