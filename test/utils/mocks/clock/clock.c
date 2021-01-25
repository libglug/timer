#include "clock.h"

// get_time
static clocktime_t times[2] = { { 0, 0 }, { 0, 0 } };

void set_time(clock_type_t clock_type, const clocktime_t *time)
{
    times[clock_type] = *time;
}

void get_time(clock_type_t clock_type, clocktime_t *time)
{
    *time = times[clock_type];
}

// get_res
static clocktime_t ress[2] = { { 0, 0 }, { 0, 0 } };

void set_res(clock_type_t clock_type, const clocktime_t *res)
{
    ress[clock_type] = *res;
}

void get_res(clock_type_t clock_type, clocktime_t *res)
{
    *res = ress[clock_type];
}
