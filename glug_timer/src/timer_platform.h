#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

#include <glug/timer/time_t.h>

struct frac;

GLUG_LIB_LOCAL void read_continuous_ticks(uint64_t *);
GLUG_LIB_LOCAL void continuous_tick_scale(struct frac *);
GLUG_LIB_LOCAL void continuous_clock_res(struct glug_time *);

#endif // GLUG_TIMER_PLATFORM_H
