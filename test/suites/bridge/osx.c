#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/frac.h>
#include <asserts/time.h>

#include <glug/timer/time_t.h>
#include <defs.h>
#include <timer_bridge.h>
#include <mocks/mach/mach.h>

void test_continuous_ticks(void)
{
    uint64_t expected = 9;
    set_continuous_ticks(&expected);

    uint64_t actual;
    read_continuous_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_continuous_tick_scale(void)
{
    frac_t expected = { 1500000000, 133 };
    set_tick_scale(&expected);

    frac_t actual;
    continuous_tick_scale(&actual);

    assert_frac_equal(&expected, &actual);
}

void test_continuous_clock_res(void)
{
    frac_t scale = { 1500000000, 133 };
    set_tick_scale(&scale);

    uint64_t freq = scale.numer / scale.denom;
    struct glug_time expected = { (uint32_t)(freq / NSEC_PER_SEC), freq % NSEC_PER_SEC };
    struct glug_time actual;
    continuous_clock_res(&actual);

    assert_time_equal(&expected, &actual);
}

void test_uptime_ticks(void)
{
    uint64_t expected = 833495108;
    set_absolute_ticks(&expected);

    uint64_t actual;
    read_uptime_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_uptime_tick_scale(void)
{
    frac_t expected = { 502675260, 554 };
    set_tick_scale(&expected);

    frac_t actual;
    uptime_tick_scale(&actual);

    assert_frac_equal(&expected, &actual);
}

void test_uptime_clock_res(void)
{
    frac_t scale = { 549626624, 2358 };
    set_tick_scale(&scale);

    uint64_t freq = scale.numer / scale.denom;
    struct glug_time expected = { (uint32_t)(freq / NSEC_PER_SEC), freq % NSEC_PER_SEC };
    struct glug_time actual;
    uptime_clock_res(&actual);

    assert_time_equal(&expected, &actual);
}

int main(void)
{
    CU_pSuite suite = create_suite("osx_bridge", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "read_continuous_ticks", test_continuous_ticks);
    CU_add_test(suite, "continuous_ticks_scale", test_continuous_tick_scale);
    CU_add_test(suite, "continuous_clock_res", test_continuous_clock_res);
    CU_add_test(suite, "read_uptime_ticks", test_uptime_ticks);
    CU_add_test(suite, "uptime_ticks_scale", test_uptime_tick_scale);
    CU_add_test(suite, "uptime_clock_res", test_uptime_clock_res);

    return run_tests(CU_BRM_VERBOSE);
}
