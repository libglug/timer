#include <CUnit/Basic.h>

#include <suites/create_suite.h>
#include <asserts/time.h>

#include <glug/timer/time_t.h>
#include <frac_t.h>
#include <tick.h>

void test_halved(void)
{
    struct glug_time actual;
    frac_t frac_half = { 1, 2 };
    uint64_t ticks = 8765432;
    scale_to_time(&ticks, &frac_half, &actual);

    struct glug_time expected = { 0, 4382716 };
    assert_time_equal(&actual, &expected);
}

void test_doubled(void)
{
    struct glug_time actual;
    frac_t frac_double = { 2, 1 };
    uint64_t ticks = 12345678;
    scale_to_time(&ticks, &frac_double, &actual);

    struct glug_time expected = { 0, 24691356 };
    assert_time_equal(&actual, &expected);
}

void test_scale_with_carry(void)
{
    struct glug_time actual;
    frac_t scale = { 77, 3 };
    uint64_t ticks = 777777777;
    scale_to_time(&ticks, &scale, &actual);

    struct glug_time expected = { 19, 962962943 };
    assert_time_equal(&actual, &expected);
}

void test_scale_round_down(void)
{
    struct glug_time actual;
    frac_t scale = { 1, 3 };
    uint64_t ticks = 12;
    scale_to_time(&ticks, &scale, &actual);

    struct glug_time expected = { 0, 4 };
    assert_time_equal(&actual, &expected);
}

void test_scale_round_up(void)
{
    struct glug_time actual;
    frac_t scale = { 1, 3 };
    uint64_t ticks = 20;
    scale_to_time(&ticks, &scale, &actual);

    struct glug_time expected = { 0, 7 };
    assert_time_equal(&actual, &expected);
}

void test_small_scale(void)
{
    struct glug_time actual;
    frac_t scale = { 1, 0xffffffff };
    uint64_t ticks = 0x7fffffffffffffff;
    scale_to_time(&ticks, &scale, &actual);

    struct glug_time expected = { 2, 147483648 };
    assert_time_equal(&actual, &expected);

    ticks = 0xdeaddeadbeeeef;
    scale_to_time(&ticks, &scale, &actual);
    expected.sec = 0;
    expected.nsec = 14593503;
    assert_time_equal(&actual, &expected);
}

void test_large_scale(void)
{
    struct glug_time actual;
    frac_t scale = { 0xffffffff, 1 };
    uint64_t ticks = 1;
    scale_to_time(&ticks, &scale, &actual);

    struct glug_time expected = { 4, 294967295 };
    assert_time_equal(&actual, &expected);

    ticks = 0xfed;
    scale_to_time(&ticks, &scale, &actual);
    expected.sec = 17510;
    expected.nsec = 581661715;
    assert_time_equal(&actual, &expected);
}

void test_large_ticks(void)
{
    struct glug_time actual;
    frac_t scale = { 2, 3 };
    uint64_t ticks = 0xffffffffffff;
    scale_to_time(&ticks, &scale, &actual);

    struct glug_time expected = { 187649, 984473770 };
    assert_time_equal(&actual, &expected);
}

int main(void)
{
    CU_pSuite suite = create_suite("utils/scale_to_time", NULL, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "halved", test_halved);
    CU_add_test(suite, "doubled", test_doubled);
    CU_add_test(suite, "scale with carry", test_scale_with_carry);
    CU_add_test(suite, "scale and round down", test_scale_round_down);
    CU_add_test(suite, "scale and round up", test_scale_round_up);

    CU_add_test(suite, "scale by a very small value", test_small_scale);
    CU_add_test(suite, "scale by a very large value", test_large_scale);
    CU_add_test(suite, "scale a large tick count", test_large_ticks);

    return run_tests(CU_BRM_VERBOSE);
}
