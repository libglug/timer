#ifndef MOCK_CLOCK_H
#define MOCK_CLOCK_H

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

void set_time(clock_type_t, const clocktime_t *);
void get_time(clock_type_t, clocktime_t *);

void set_res(clock_type_t, const clocktime_t *);
void get_res(clock_type_t, clocktime_t *);

#endif // MOCK_CLOCK_H
