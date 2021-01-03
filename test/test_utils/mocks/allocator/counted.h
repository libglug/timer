#ifndef MOCK_ALLOC_COUNTED_H
#define MOCK_ALLOC_COUNTED_H

#include <glug/allocator_t.h>
#include <stdint.h>

struct glug_allocator get_counted_allocator(void);
uint32_t alloc_count(void);
void reset_alloc_count(void);

uint32_t free_count(void);
void reset_free_count(void);

#endif // MOCK_ALLOC_COUNTED_H
