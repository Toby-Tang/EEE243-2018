cmake_minimum_required(VERSION 3.0)
project(Lab3_RobotFollow C)

set(CMAKE_C_STANDARD 99)

# the toolchain file
set(CMAKE_TOOLCHAIN_FILE avr.cmake)

# necessary settings for the chip we use
set(MCU         atmega328p)
set(F_CPU       2000000)

# adding the normal avr targets (a directory contains subdirs with targets)
add_executable_avr(robot src/main.c)