set(TEST_TARGET "clock-linux")

set(TEST_SOURCE suites/clock/clock.c)

list(
    APPEND
    TEST_LIB_SOURCE
    clock/clock.h
    clock/clock.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/glug/os.h
    mocks/time.h
    mocks/time.c
)

list(
    APPEND
    TEST_DEFS
    GLUG_OS_LIN=1
    GLUG_OS=1
)

list(
    APPEND
    TEST_MOCKS
    clock_gettime
    clock_getres
)

set(TEST_INCLUDE_DIRS)
