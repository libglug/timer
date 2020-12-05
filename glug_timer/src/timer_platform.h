#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <stdint.h>

struct glug_time;
struct frac;

GLUG_LIB_LOCAL void read_continuous_ticks(uint64_t *);
GLUG_LIB_LOCAL void continuous_tick_scale(struct frac *);
GLUG_LIB_LOCAL void continuous_clock_res(struct glug_time *);

GLUG_LIB_LOCAL void read_uptime_ticks(uint64_t *);
GLUG_LIB_LOCAL void uptime_tick_scale(struct frac *);
GLUG_LIB_LOCAL void uptime_clock_res(struct glug_time *);

#endif // GLUG_TIMER_PLATFORM_H
