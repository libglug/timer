#ifndef GLUG_TIME_H
#define GLUG_TIME_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/timer/time_t.h>

GLUG_EXTERN_START

glug_time_t GLUG_LIB_API    glug_time_from_sec (double secs);
glug_time_t GLUG_LIB_API    glug_time_from_msec(double msecs);
glug_time_t GLUG_LIB_API    glug_time_from_usec(double usecs);

double      GLUG_LIB_API    glug_sec_from_time (glug_time_t);
double      GLUG_LIB_API    glug_msec_from_time(glug_time_t);
double      GLUG_LIB_API    glug_usec_from_time(glug_time_t);

GLUG_EXTERN_END

#endif // GLUG_TIME_H
