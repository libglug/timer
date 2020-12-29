set(TEST_TARGET "tick_scale")

set(TEST_SOURCE suites/tick/tick.c)

list(
    APPEND
    TEST_LIB_SOURCE
    tick.h
    tick.c
)

set(TEST_INCLUDE_DIRS)
