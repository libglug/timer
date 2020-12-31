#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/frac.h>
#include <asserts/time.h>

#include <glug/timer/time_t.h>
#include <defs.h>
#include <frac_t.h>
#include <timer_bridge.h>
#include <mocks/qpc/qpc.h>
#include <mocks/qpc/quit.h>

void test_continuous_ticks(void)
{
    uint64_t expected = 9;
    set_counter(&expected);

    uint64_t actual;
    read_continuous_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_continuous_tick_scale(void)
{
    uint64_t expected_den = 9;
    set_frequency(&expected_den);

    frac_t expected = { NSEC_PER_SEC, expected_den };
    frac_t actual;
    continuous_tick_scale(&actual);

    assert_frac_equal(&actual, &expected);
}

void test_continuous_clock_res(void)
{
    uint64_t freq_scale = 133;
    uint64_t expected_freq = NSEC_PER_SEC / freq_scale;
    set_frequency(&expected_freq);

    struct glug_time expected = { NSEC_PER_SEC <= freq_scale, (uint32_t)freq_scale };
    struct glug_time actual;
    continuous_clock_res(&actual);

    assert_time_equal(&expected, &actual);

    freq_scale = NSEC_PER_SEC;
    expected_freq = NSEC_PER_SEC / freq_scale;
    set_frequency(&expected_freq);

    expected.sec = NSEC_PER_SEC <= freq_scale;
    expected.nsec = freq_scale % NSEC_PER_SEC;
    continuous_clock_res(&actual);

    assert_time_equal(&expected, &actual);
}

void test_uptime_ticks(void)
{
    uint64_t expected = 8675309;
    set_unbiased_time(&expected);

    uint64_t actual;
    read_uptime_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_uptime_tick_scale(void)
{
    uint64_t expected_den = 1248163264;
    set_unbiased_frequency(&expected_den);

    frac_t expected = { NSEC_PER_SEC, expected_den };
    frac_t actual;
    uptime_tick_scale(&actual);

    assert_frac_equal(&actual, &expected);
}

void test_uptime_clock_res(void)
{
    uint64_t freq_scale = 666;
    uint64_t expected_freq = NSEC_PER_SEC / freq_scale;
    set_unbiased_frequency(&expected_freq);

    struct glug_time expected = { NSEC_PER_SEC <= freq_scale, (uint32_t)freq_scale };
    struct glug_time actual;
    uptime_clock_res(&actual);

    assert_time_equal(&expected, &actual);

    freq_scale = NSEC_PER_SEC;
    expected_freq = NSEC_PER_SEC / freq_scale;
    set_unbiased_frequency(&expected_freq);

    expected.sec = NSEC_PER_SEC <= freq_scale;
    expected.nsec = freq_scale % NSEC_PER_SEC;
    uptime_clock_res(&actual);

    assert_time_equal(&expected, &actual);
}

int main(void)
{
    CU_pSuite suite = create_suite("win32_bridge", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "read_continuous_ticks", test_continuous_ticks);
    CU_add_test(suite, "continuous_ticks_scale", test_continuous_tick_scale);
    CU_add_test(suite, "continuous_clock_res", test_continuous_clock_res);
    CU_add_test(suite, "read_uptime_ticks", test_uptime_ticks);
    CU_add_test(suite, "uptime_ticks_scale", test_uptime_tick_scale);
    CU_add_test(suite, "uptime_clock_res", test_uptime_clock_res);

    return run_tests(CU_BRM_VERBOSE);
}
