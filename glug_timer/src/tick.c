#include "time.h"
#include "defs.h"

#include <math.h>
#include <glug/timer/time_t.h>
#include <frac.h>

#include <stdlib.h>

void scale_to_time(const uint64_t *ticks, const struct frac *scale, struct glug_time *time)
{
    // a potential loss of precision
    double lfscale = (double)scale->numer / scale->denom;

    uint64_t high = (HIGH_U64(*ticks) << 32) * lfscale;
    lldiv_t highdiv = lldiv(high, NSEC_PER_SEC);

    uint64_t low = (uint64_t)(LOW_U64(*ticks) * lfscale + 0.5) + highdiv.rem;
    lldiv_t lowdiv = lldiv(low, NSEC_PER_SEC);

    time->nsec = lowdiv.rem;
    time->sec  = highdiv.quot + lowdiv.quot;
}
