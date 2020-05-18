#include "mach.h"

#include <mach/mach_time.h>

uint64_t continuous_ticks(void)
{
    return mach_continuous_time();
}

uint64_t absolute_ticks(void)
{
    return mach_absolute_time();
}

void tick_scale(mach_timebase_info_data_t *tick_scale)
{
    mach_timebase_info(tick_scale);
}
