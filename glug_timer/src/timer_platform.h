#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

uint64_t clock_res();
uint64_t clock_frequency();
uint64_t read_clock();

#endif // GLUG_TIMER_PLATFORM_H
