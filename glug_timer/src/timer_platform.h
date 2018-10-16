#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

uint64_t read_clock();
uint64_t clock_to_nsec(uint64_t clock);
uint64_t clock_res();

#endif // GLUG_TIMER_PLATFORM_H
