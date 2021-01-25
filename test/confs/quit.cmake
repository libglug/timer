set(TEST_TARGET "quit")

set(TEST_SOURCE suites/qpc/quit.c)

list(
    APPEND
    TEST_LIB_SOURCE
    qpc/quit.h
    qpc/quit.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/Windows.h
    mocks/Windows.c
)

list(
    APPEND
    TEST_MOCKS
    QueryPerformanceCounter
    QueryPerformanceFrequency
    QueryUnbiasedInterruptTime
)

set(TEST_INCLUDE_DIRS)
