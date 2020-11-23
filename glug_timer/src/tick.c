#include "time.h"
#include "defs.h"

#include <math.h>
#include <glug/timer/time_t.h>
#include <frac.h>

void scale_to_time(uint64_t ticks, struct frac *scale, struct glug_time *time)
{
    // a potential loss of precision
    double lfscale = (double)scale->numer / scale->denom;

    uint64_t high = (HIGH_U64(ticks) << 32) * lfscale;
    uint64_t sec = high / NSEC_PER_SEC;
    uint32_t borrow = high % NSEC_PER_SEC;

    uint64_t low = (uint64_t)(LOW_U64(ticks) * lfscale + 0.5) + borrow;
    uint32_t nsec  = low % NSEC_PER_SEC;
    uint32_t carry = low / NSEC_PER_SEC;

    time->nsec = nsec;
    time->sec  = sec + carry;
}
