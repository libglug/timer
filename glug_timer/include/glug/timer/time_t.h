#ifndef GLUG_TIME_T_H
#define GLUG_TIME_T_H

#include <stdint.h>

typedef uint64_t glug_time_t;
struct glug_timer;

#ifdef GLUG_USE_TYPEDEFS
    typedef struct glug_timer glug_timer_t;
#endif

#endif // GLUG_TIME_T_H
