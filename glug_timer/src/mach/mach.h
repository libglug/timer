#ifndef GLUG_MACH_H
#define GLUG_MACH_H

#include <stdint.h>

typedef struct
{
    uint32_t numer;
    uint32_t denom;
} frac_t;

GLUG_LIB_LOCAL uint64_t continuous_ticks(void);
GLUG_LIB_LOCAL uint64_t absolute_ticks(void);

GLUG_LIB_LOCAL void     tick_scale(frac_t *);

#endif // GLUG_MACH_H
