#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

GLUG_LIB_LOCAL uint64_t read_clock(void);
GLUG_LIB_LOCAL uint64_t clock_to_nsec(uint64_t clock);
GLUG_LIB_LOCAL uint64_t clock_res(void);

#endif // GLUG_TIMER_PLATFORM_H
