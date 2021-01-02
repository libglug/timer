#ifndef MOCK_GLUG_ALLOCATOR_H
#define MOCK_GLUG_ALLOCATOR_H

#include <stddef.h>

typedef void *(*glug_malloc_t) (size_t nbytes);
typedef void  (*glug_free_t)   (void *block);

struct glug_allocator
{
    glug_malloc_t  malloc;
    glug_free_t    free;
};

#endif // MOCK_GLUG_ALLOCATOR_H
