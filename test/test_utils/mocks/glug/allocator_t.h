#ifndef MOCK_GLUG_ALLOCATOR_H
#define MOCK_GLUG_ALLOCATOR_H

#include <stddef.h>

typedef void *(*glug_malloc_t) (size_t nbytes, void *context);
typedef void  (*glug_free_t)   (void *block, void *context);

struct glug_allocator
{
    glug_malloc_t   malloc;
    glug_free_t     free;
    void           *context;
};

#endif // MOCK_GLUG_ALLOCATOR_H
