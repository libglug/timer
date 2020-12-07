#include "quit.h"
#include <defs.h>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void query_unbiased_frequency(uint64_t *frequency)
{
    *frequency = NSEC_PER_SEC / 100;
}

void query_unbiased_time(uint64_t *ticks)
{
    QueryUnbiasedInterruptTime(ticks);
}
