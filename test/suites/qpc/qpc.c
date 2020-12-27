#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>

#include <qpc/qpc.h>

#include <Windows.h>

void test_query_frequency(void)
{
    uint64_t expected = 123456789;
    set_QueryPerformanceFrequency(&expected);

    uint64_t actual;
    query_frequency(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_query_counter(void)
{
    uint64_t expected = 87871234;
    set_QueryPerformanceCounter(&expected);

    uint64_t actual;
    query_counter(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

int main(void)
{
    CU_pSuite suite = create_suite("qpc", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "query_frequency", test_query_frequency);
    CU_add_test(suite, "query_counter", test_query_counter);

    return run_tests(CU_BRM_VERBOSE);
}
