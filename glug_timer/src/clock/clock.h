#ifndef GLUG_CLOCK_H
#define GLUG_CLOCK_H

#include <time.h>

GLUG_LIB_LOCAL void get_time(struct timespec *);
GLUG_LIB_LOCAL void get_res (struct timespec *);

#endif // GLUG_CLOCK_H
