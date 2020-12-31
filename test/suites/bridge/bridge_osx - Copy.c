#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>

#include <timer_bridge.h>
//#include <mocks/>

void test_continuous_ticks(void)
{

}

void test_continuous_tick_scale(void)
{

}

void test_continuous_clock_res(void)
{

}

void test_uptime_ticks(void)
{

}

void test_uptime_tick_scale(void)
{

}

void test_uptime_clock_res(void)
{

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
