#include "tick.h"
#include "defs.h"

#include <math.h>
#include <glug/timer/time_t.h>
#include <frac_t.h>

#include <stdlib.h>

void scale_to_time(const uint64_t *ticks, const struct frac *scale, struct glug_time *time)
{
    // a potential loss of precision
    double lfscale = (double)scale->numer / scale->denom;

    uint64_t high = (uint64_t)(HIGH_MASK_U64(*ticks) * lfscale);
    lldiv_t highdiv = lldiv(high, NSEC_PER_SEC);

    uint64_t low = (uint64_t)(LOW_MASK_U64(*ticks) * lfscale + 0.5) + highdiv.rem;
    lldiv_t lowdiv = lldiv(low, NSEC_PER_SEC);

    time->nsec = (uint32_t)lowdiv.rem;
    time->sec  = (uint32_t)(highdiv.quot + lowdiv.quot);
}
