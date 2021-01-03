set(TEST_TARGET "uptime_timer")

set(TEST_SOURCE suites/timer/uptime.c)

list(
    APPEND
    TEST_LIB_SOURCE
    uptime_timer.c
    timer.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/allocator/counted.h
    mocks/allocator/counted.c
    mocks/timer_bridge.h
    mocks/timer_bridge.c
    mocks/tick.h
    mocks/tick.c
)

list(
    APPEND
    TEST_DEFS
    GLUG_EXTERN_START=
    GLUG_EXTERN_END=
)

set(TEST_INCLUDE_DIRS)
