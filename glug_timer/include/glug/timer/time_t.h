#ifndef GLUG_TIME_T_H
#define GLUG_TIME_T_H

#include <stdint.h>

struct glug_time
{
    uint32_t sec;
    uint32_t nsec;
};

#ifdef GLUG_USE_TYPEDEFS
    typedef struct glug_time glug_time_t;
#endif

#endif // GLUG_TIME_T_H
