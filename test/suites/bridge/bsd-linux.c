#include "bsd-linux.h"

#include <CUnit/Assert.h>

#include <asserts/frac.h>
#include <asserts/time.h>

#include <glug/timer/time_t.h>
#include <defs.h>
#include <frac_t.h>
#include <timer_bridge.h>
#include <mocks/clock/clock.h>

void test_continuous_ticks(void)
{
    clocktime_t expected_ct = { 14, 563900233 };
    set_time(CONTINUOUS, &expected_ct);

    uint64_t expected = expected_ct.sec * (uint64_t)NSEC_PER_SEC + expected_ct.nsec;
    uint64_t actual;
    read_continuous_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_continuous_tick_scale(void)
{
    frac_t expected = { 1, 1 };

    frac_t actual;
    continuous_tick_scale(&actual);

    assert_frac_equal(&expected, &actual);
}

void test_continuous_clock_res(void)
{
    clocktime_t expected_ct = { 1, 49766952 };
    set_res(CONTINUOUS, &expected_ct);

    struct glug_time expected = { expected_ct.sec, expected_ct.nsec };
    struct glug_time actual;
    continuous_clock_res(&actual);

    assert_time_equal(&expected, &actual);
}

void test_uptime_ticks(void)
{
    clocktime_t expected_ct = { 7, 8447151 };
    set_time(UPTIME, &expected_ct);

    uint64_t expected = expected_ct.sec * (uint64_t)NSEC_PER_SEC + expected_ct.nsec;
    uint64_t actual;
    read_uptime_ticks(&actual);

    CU_ASSERT_EQUAL(expected, actual);
}

void test_uptime_tick_scale(void)
{
    frac_t expected = { 1, 1 };

    frac_t actual;
    uptime_tick_scale(&actual);

    assert_frac_equal(&expected, &actual);
}

void test_uptime_clock_res(void)
{
    clocktime_t expected_ct = { 2, 75764165 };
    set_res(UPTIME, &expected_ct);

    struct glug_time expected = { expected_ct.sec, expected_ct.nsec };
    struct glug_time actual;
    uptime_clock_res(&actual);

    assert_time_equal(&expected, &actual);
}
