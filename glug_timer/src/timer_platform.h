#ifndef GLUG_TIMER_PLATFORM_H
#define GLUG_TIMER_PLATFORM_H

#include <frac.h>
#include <stdint.h>

GLUG_LIB_LOCAL uint64_t read_clock_ticks(void);
GLUG_LIB_LOCAL void     ticks_per_sec(frac_t *);
GLUG_LIB_LOCAL uint64_t clock_res(void);

#endif // GLUG_TIMER_PLATFORM_H
