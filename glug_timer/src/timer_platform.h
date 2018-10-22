#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

uint64_t GLUG_LIB_LOCAL read_clock();
uint64_t GLUG_LIB_LOCAL clock_to_nsec(uint64_t clock);
uint64_t GLUG_LIB_LOCAL clock_res();

#endif // GLUG_TIMER_PLATFORM_H
