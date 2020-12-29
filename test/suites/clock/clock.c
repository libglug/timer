#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/clocktime.h>

#include <clock/clock.h>
#include <time.h>

void test_clock_gettime(void)
{
    struct timespec boottime_ts = { 715, 9876123 };
    set_clock_gettime(CLOCK_BOOTTIME, &boottime_ts);
    struct timespec monotonic_ts = { 321, 6789517 };
    set_clock_gettime(CLOCK_MONOTONIC_RAW, &monotonic_ts);

    clocktime_t expected_boottime = { (uint32_t)boottime_ts.tv_sec, boottime_ts.tv_nsec };
    clocktime_t actual_boottime;
    get_time(CONTINUOUS, &actual_boottime);

    assert_clocktime_equal(&expected_boottime, &actual_boottime);

    clocktime_t expected_monotonic = { (uint32_t)monotonic_ts.tv_sec, monotonic_ts.tv_nsec };
    clocktime_t actual_monotonic;
    get_time(UPTIME, &actual_monotonic);

    assert_clocktime_equal(&expected_monotonic, &actual_monotonic);
}

void test_clock_getres(void)
{
    struct timespec monotonic_ts = { 1596, 332251757 };
    set_clock_getres(CLOCK_MONOTONIC, &monotonic_ts);
    struct timespec uptime_ts = { 7571, 522336951 };
    set_clock_getres(CLOCK_UPTIME, &uptime_ts);

    clocktime_t expected_monotonic = { (uint32_t)monotonic_ts.tv_sec, monotonic_ts.tv_nsec };
    clocktime_t actual_monotonic;
    get_res(CONTINUOUS, &actual_monotonic);

    assert_clocktime_equal(&expected_monotonic, &actual_monotonic);

    clocktime_t expected_uptime = { (uint32_t)uptime_ts.tv_sec, uptime_ts.tv_nsec };
    clocktime_t actual_uptime;
    get_res(UPTIME, &actual_uptime);

    assert_clocktime_equal(&expected_uptime, &actual_uptime);
}

int main(void)
{
    CU_pSuite suite = create_suite("clock", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "clock_gettime", test_clock_gettime);
    CU_add_test(suite, "clock_getres", test_clock_getres);

    return run_tests(CU_BRM_VERBOSE);
}
