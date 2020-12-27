#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>

#include <qpc/quit.h>

#include <Windows.h>

void test_unbiased_frequency(void)
{
    uint64_t expected;
    query_unbiased_frequency(&expected);

    uint64_t actual = 1000 * 1000 * 1000 / 100; // unbiased time is always the number of 100ns ticks
    CU_ASSERT_EQUAL(expected, actual);
}

void test_unbiased_time(void)
{
    uint64_t expected = 1111111111111;
    set_UnbiasedInterruptTime(&expected);

    uint64_t actual;
    query_unbiased_time(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

int main(void)
{
    CU_pSuite suite = create_suite("quit", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "unbiased_frequency", test_unbiased_frequency);
    CU_add_test(suite, "unbiased_time", test_unbiased_time);

    return run_tests(CU_BRM_VERBOSE);
}
