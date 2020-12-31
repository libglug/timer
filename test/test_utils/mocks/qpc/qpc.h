#ifndef MOCK_QPC_H
#define MOCK_QPC_H

#include <stdint.h>

void set_frequency(uint64_t *);
void query_frequency(uint64_t *);

void set_counter(const uint64_t *);
void query_counter(uint64_t *);

#endif // MOCK_QPC_H
