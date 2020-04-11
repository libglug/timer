#ifndef GLUG_TIME_H
#define GLUG_TIME_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/timer/time_t.h>

GLUG_EXTERN_START

GLUG_LIB_API glug_time_t glug_time_from_sec (double secs);
GLUG_LIB_API glug_time_t glug_time_from_msec(double msecs);
GLUG_LIB_API glug_time_t glug_time_from_usec(double usecs);

GLUG_LIB_API double      glug_sec_from_time (glug_time_t);
GLUG_LIB_API double      glug_msec_from_time(glug_time_t);
GLUG_LIB_API double      glug_usec_from_time(glug_time_t);

GLUG_EXTERN_END

#endif // GLUG_TIME_H
