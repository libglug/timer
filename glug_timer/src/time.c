#include <glug/timer/time.h>
#include <glug/timer/time_t.h>

glug_time_t GLUG_LIB_API glug_time_from_sec(double secs)
{
    return glug_time_from_msec(1000 * secs);
}

glug_time_t GLUG_LIB_API glug_time_from_msec(double msecs)
{
    return glug_time_from_usec(1000 * msecs);
}

glug_time_t GLUG_LIB_API glug_time_from_usec(double usecs)
{
    return (glug_time_t)(1000 * usecs);
}

double GLUG_LIB_API glug_sec_from_time(glug_time_t time)
{
    return glug_msec_from_time(time) / 1000.0;
}

double GLUG_LIB_API glug_msec_from_time(glug_time_t time)
{
    return glug_usec_from_time(time) / 1000.0;
}

double GLUG_LIB_API glug_usec_from_time(glug_time_t time)
{
    return time / 1000.0;
}

