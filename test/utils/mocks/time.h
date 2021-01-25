#ifndef MOCK_TIME_H
#define MOCK_TIME_H

#include <stdint.h>

// Linux clocks
#define CLOCK_BOOTTIME 0
#define CLOCK_MONOTONIC_RAW 1

// BSD clocks
#define CLOCK_MONOTONIC 0
#define CLOCK_UPTIME 1

typedef int clockid_t;
struct timespec
{
    int64_t tv_sec;
    int32_t tv_nsec;
};

void set_clock_gettime(clockid_t, const struct timespec *);
int clock_gettime(clockid_t, struct timespec *);

void set_clock_getres(clockid_t, const struct timespec *);
int clock_getres(clockid_t, struct timespec *);

#endif // MOCK_TIME_H
