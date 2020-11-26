#ifndef GLUG_MACH_H
#define GLUG_MACH_H

#include <frac.h>
#include <stdint.h>

GLUG_LIB_LOCAL void continuous_ticks(uint64_t *);
GLUG_LIB_LOCAL void absolute_ticks(uint64_t *);

GLUG_LIB_LOCAL void tick_scale(frac_t *);

#endif // GLUG_MACH_H
