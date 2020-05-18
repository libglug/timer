#include "timer_platform.h"
#include <glug/os.h>

#if GLUG_OS == GLUG_OS_UNK

uint64_t read_clock(void)
{
    return 0;
}

uint64_t clock_to_nsec(uint64_t clock)
{
    (void) clock;
    return 0;
}

uint64_t clock_res(void)
{
    return -1;
}

#endif // GLUG_OS == GLUG_OS_UNK
