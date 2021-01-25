set(TEST_TARGET "mach")

set(TEST_SOURCE suites/mach/mach.c)

list(
    APPEND
    TEST_LIB_SOURCE
    mach/mach.h
    mach/mach.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/mach/mach_time.h
    mocks/mach/mach_time.c
)

list(
    APPEND
    TEST_MOCKS
    mach_continuous_time
    mach_absolute_time
    mach_timebase_info
)

set(TEST_INCLUDE_DIRS)
