#ifndef MOCK_TIMER_BRIDGE_H
#define MOCK_TIMER_BRIDGE_H

#include <stdint.h>

struct glug_time;
struct frac;

void set_continuous_ticks(const uint64_t *);
void read_continuous_ticks(uint64_t *);

void set_continuous_scale(const struct frac *);
void continuous_tick_scale(struct frac *);

void set_continuous_res(const struct glug_time *);
void continuous_clock_res(struct glug_time *);

void set_uptime_ticks(const uint64_t *);
void read_uptime_ticks(uint64_t *);

void set_uptime_scale(const struct frac *);
void uptime_tick_scale(struct frac *);

void set_uptime_res(const struct glug_time *);
void uptime_clock_res(struct glug_time *);

#endif // MOCK_TIMER_BRIDGE_H
