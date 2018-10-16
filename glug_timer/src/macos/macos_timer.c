#include "../timer_platform.h"

#include <stdint.h>
#include <mach/mach_time.h>

static mach_timebase_info_data_t clock_frequency()
{
    mach_timebase_info_data_t frequency;
    mach_timebase_info(&frequency);
    return frequency;
}

uint64_t read_clock()
{
    return mach_absolute_time();
}

uint64_t clock_to_nsec(uint64_t clock)
{
    mach_timebase_info_data_t frequency = clock_frequency();
    return clock * frequency.numer / frequency.denom;
}

uint64_t clock_res()
{
    mach_timebase_info_data_t frequency = clock_frequency();
    return frequency.numer / frequency.denom;
}
