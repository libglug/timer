#ifndef GLUG_MACH_H
#define GLUG_MACH_H

#include <stdint.h>
#include <mach/mach_time.h>

GLUG_LIB_LOCAL uint64_t continuous_ticks(void);
GLUG_LIB_LOCAL uint64_t absolute_ticks(void);

GLUG_LIB_LOCAL void     tick_scale(mach_timebase_info_data_t *);

#endif // GLUG_MACH_H
