#include "qpc.h"

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void query_frequency(LARGE_INTEGER *freq)
{
    QueryPerformanceFrequency(freq);
}

void query_counter(LARGE_INTEGER *counter)
{
    QueryPerformanceCounter(counter);
}
