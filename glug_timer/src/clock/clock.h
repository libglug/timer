#ifndef GLUG_CLOCK_H
#define GLUG_CLOCK_H

#include <time.h>

GLUG_LIB_LOCAL void get_time(clockid_t, struct timespec *);
GLUG_LIB_LOCAL void get_res (clockid_t, struct timespec *);

#endif // GLUG_CLOCK_H
