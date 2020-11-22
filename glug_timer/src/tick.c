#include "time.h"
#include "defs.h"

#include <glug/timer/time_t.h>
#include <frac.h>

void scale_to_time(uint64_t ticks, struct frac *scale, struct glug_time *time)
{
    double dscale = (double)scale->numer / scale->denom;

    uint64_t high = HIGH_U64(ticks);
    uint64_t low  = LOW_U64(ticks);
    uint64_t carry = (uint64_t)(low * dscale) / NSEC_PER_SEC;

    time->nsec = (uint64_t)(low * dscale) % NSEC_PER_SEC;
    time->sec = high * dscale + carry;
}
