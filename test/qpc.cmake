set(TEST_TARGET "qpc")

set(TEST_SOURCE suites/qpc/qpc.c)

list(
    APPEND
    TEST_LIB_SOURCE
    qpc/qpc.h
    qpc/qpc.c
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
)

set(TEST_INCLUDE_DIRS)
