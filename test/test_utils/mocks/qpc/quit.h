#ifndef MOCK_QUIT_H
#define MOCK_QUIT_H

#include <stdint.h>

void set_unbiased_frequency(const uint64_t *);
void query_unbiased_frequency(uint64_t *);

void set_unbiased_time(const uint64_t *);
void query_unbiased_time(uint64_t *);

#endif // MOCK_QUIT_H
