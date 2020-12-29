#ifndef MOCK_MACH_TIME_H
#define MOCK_MACH_TIME_H

#include <stdint.h>

typedef struct
{
    uint32_t numer;
    uint32_t denom;
} mach_timebase_info_data_t;

typedef int kern_return_t;

void set_mach_continuous_time(const uint64_t *);
uint64_t mach_continuous_time(void);

void set_mach_absolute_time(const uint64_t *);
uint64_t mach_absolute_time(void);

void set_mach_timebase_info(const mach_timebase_info_data_t *);
kern_return_t mach_timebase_info(mach_timebase_info_data_t *);


#endif // MOCK_MACH_TIME_H
