#include "counted.h"

#include <stdlib.h>

static uint32_t allocs = 0;
static uint32_t frees = 0;

static void *counted_alloc(size_t nbytes)
{
    ++allocs;
    return malloc(nbytes);
}

static void counted_free(void *block)
{
    ++frees;
    free(block);
}

struct glug_allocator get_counted_allocator(void)
{
    return (struct glug_allocator)
    {
        counted_alloc,
        counted_free,
    };
}

uint32_t alloc_count(void)
{
    return allocs;
}

void reset_alloc_count(void)
{
    allocs = 0;
}

uint32_t free_count(void)
{
    return frees;
}

void reset_free_count(void)
{
    frees = 0;
}
