#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

#include <glug/timer/time_t.h>

struct frac;

GLUG_LIB_LOCAL void read_clock_ticks(uint64_t *);
GLUG_LIB_LOCAL void secs_per_tick(struct frac *);
GLUG_LIB_LOCAL void clock_res(struct glug_time *);

#endif // GLUG_TIMER_PLATFORM_H
