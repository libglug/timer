#include "tick.h"

#include <glug/timer/time_t.h>
#include <defs.h>

static struct scale_args last_call_args = { 0, { 1, 1 } };

void scale_to_time(const uint64_t *ticks, const struct frac *scale, struct glug_time *time)
{
    last_call_args.ticks = *ticks;
    last_call_args.scale = *scale;

    time->sec  = (uint32_t)(*ticks / NSEC_PER_SEC);
    time->nsec = (uint32_t)(*ticks % NSEC_PER_SEC);
}

struct scale_args get_scale_last_args(void)
{
    return last_call_args;
}
