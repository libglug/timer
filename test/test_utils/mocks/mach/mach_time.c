#include "mach_time.h"

// mach_continuous_time
static uint64_t continuous_time = 0;
void set_mach_continuous_time(const uint64_t *time)
{
    continuous_time = *time;
}

uint64_t mach_continuous_time(void)
{
    return continuous_time;
}

// mach_absolute_time
static uint64_t absolute_time = 0;
void set_mach_absolute_time(const uint64_t *time)
{
    absolute_time = *time;
}

uint64_t mach_absolute_time(void)
{
    return absolute_time;
}

// mach_timebase_info
static mach_timebase_info_data_t timebase_info = {0, 0};
void set_mach_timebase_info(const mach_timebase_info_data_t *timebase)
{
    timebase_info = *timebase;
}

kern_return_t mach_timebase_info(mach_timebase_info_data_t *timebase)
{
    *timebase = timebase_info;

    return 0;
}
