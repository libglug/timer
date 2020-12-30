set(TEST_TARGET "bridge-win32")

set(TEST_SOURCE suites/bridge/win32.c)

list(
    APPEND
    TEST_LIB_SOURCE
    timer_bridge_win32.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/qpc/qpc.h
    mocks/qpc/qpc.c
    mocks/qpc/quit.h
    mocks/qpc/quit.c
)

list(
    APPEND
    TEST_MOCKS
)

