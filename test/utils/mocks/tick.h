#ifndef MOCK_TICK_H
#define MOCK_TICK_H

#include <stdint.h>
#include <frac_t.h>

struct glug_time;

struct scale_args
{
    uint64_t ticks;
    struct frac scale;
};

void scale_to_time(const uint64_t *, const struct frac *, struct glug_time *);
struct scale_args get_scale_last_args(void);

#endif // MOCK_TICK_H
