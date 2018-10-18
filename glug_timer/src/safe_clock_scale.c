#include <stdint.h>

uint64_t safe_clock_scale(uint64_t clock, uint64_t numer, uint64_t denom)
{
    // split 'clock' into high, low, and carry 32-bit blocks
    uint64_t high = (clock >> 32) * numer;
    uint64_t low = (clock & 0xffffffffull) * numer;
    uint64_t carry = (high % denom) << 32;

    high  /= denom;
    low   /= denom;
    carry /= denom;

    return (high << 32) + carry + low;
}
