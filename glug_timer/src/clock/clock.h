#ifndef GLUG_CLOCK_H
#define GLUG_CLOCK_H

#include <stdint.h>

typedef enum
{
    CONTINUOUS,
    UPTIME
} clock_type_t;

typedef struct
{
    uint32_t sec;
    uint32_t nsec;
} clocktime_t;

GLUG_LIB_LOCAL void get_time(clock_type_t, clocktime_t *);
GLUG_LIB_LOCAL void get_res (clock_type_t, clocktime_t *);

#endif // GLUG_CLOCK_H
