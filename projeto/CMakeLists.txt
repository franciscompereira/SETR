cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(test_pwm_circuit)

target_sources(app PRIVATE src/main.c src/heater_PWM.c src/adc_temp.c src/control.c src/pid.c src/UI.c src/database.c src/display_uart.c)
