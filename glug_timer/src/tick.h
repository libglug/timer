#ifndef GLUG_TICK_H
#define GLUG_TICK_H

#include <stdint.h>

struct frac;
struct glug_time;

void scale_to_time(uint64_t *, struct frac *, struct glug_time *);

#endif // GLUG_TICK_H
