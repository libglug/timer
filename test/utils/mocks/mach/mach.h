#ifndef MOCK_MACH_H
#define MOCK_MACH_H

#include <frac_t.h>
#include <stdint.h>

void set_continuous_ticks(const uint64_t *);
void continuous_ticks(uint64_t *);

void set_absolute_ticks(const uint64_t *);
void absolute_ticks(uint64_t *);

void set_tick_scale(const frac_t *);
void tick_scale(frac_t *);

#endif // MOCK_MACH_H
