#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/frac.h>

#include <mach/mach.h>
#include <mach/mach_time.h>

#include <frac_t.h>

void test_continuous_ticks(void)
{
    uint64_t expected = 12341234123412341234ULL;
    set_mach_continuous_time(&expected);

    uint64_t actual;
    continuous_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_absolute_ticks(void)
{
    uint64_t expected = 11112222333344445555ULL;
    set_mach_absolute_time(&expected);

    uint64_t actual;
    absolute_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_tick_scale(void)
{
    mach_timebase_info_data_t expected_tb = {54321, 1500000000};
    set_mach_timebase_info(&expected_tb);

    frac_t expected;
    expected.numer = expected_tb.numer;
    expected.denom = expected_tb.denom;

    frac_t actual;
    tick_scale(&actual);

    assert_frac_equal(&expected, &actual);
}

int main(void)
{
    CU_pSuite suite = create_suite("mach", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "continuous_ticks", test_continuous_ticks);
    CU_add_test(suite, "absolute_ticks", test_absolute_ticks);
    CU_add_test(suite, "tick_scale", test_tick_scale);

    return run_tests(CU_BRM_VERBOSE);
}
