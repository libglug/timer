#include "qpc.h"

// query_frequency
static uint64_t frequency = 0;
void set_frequency(uint64_t *freq)
{
    frequency = *freq;
}
void query_frequency(uint64_t *freq)
{
    *freq = frequency;
}

// query_counter
static uint64_t counter = 0;
void set_counter(const uint64_t *count)
{
    counter = *count;
}

void query_counter(uint64_t *count)
{
    *count = counter;
}
