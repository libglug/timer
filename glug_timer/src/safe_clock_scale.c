#include "safe_clock_scale.h"

#include <stdint.h>

uint64_t safe_clock_scale(uint64_t clock, const frac_t *scale)
{
    // split 'clock' into high, low, and carry 32-bit blocks
    uint64_t high = (clock >> 32) * scale->numer;
    uint64_t low = (clock & 0xffffffffull) * scale->numer;
    uint64_t carry = (high % scale->denom) << 32;

    high  /= scale->denom;
    low   /= scale->denom;
    carry /= scale->denom;

    return (high << 32) + carry + low;
}
