set(TEST_TARGET "bridge-linux")

set(TEST_SOURCE
    suites/bridge/linux.c
    suites/bridge/bsd-linux.h
    suites/bridge/bsd-linux.c
)

list(
    APPEND
    TEST_LIB_SOURCE
    timer_bridge_linux.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/clock/clock.h
    mocks/clock/clock.c
)

list(
    APPEND
    TEST_MOCKS
)

