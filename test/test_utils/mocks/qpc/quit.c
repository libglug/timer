#include "quit.h"

// query_unbiased_frequency
static uint64_t frequency = 0;
void set_unbiased_frequency(const uint64_t *freq)
{
    frequency = *freq;
}

void query_unbiased_frequency(uint64_t *freq)
{
    *freq = frequency;
}

// query_unbiased_time
static uint64_t time = 0;
void set_unbiased_time(const uint64_t *unbiased)
{
    time = *unbiased;
}

void query_unbiased_time(uint64_t *unbiased)
{
    *unbiased = time;
}
