set(TEST_TARGET "bridge-osx")

set(TEST_SOURCE suites/bridge/osx.c)

list(
    APPEND
    TEST_LIB_SOURCE
    timer_bridge_osx.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/mach/mach.h
    mocks/mach/mach.c
)

list(
    APPEND
    TEST_MOCKS
)

