﻿#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/time.h>
#include <asserts/frac.h>

#include <glug/timer/continuous_timer_t.h>
#include <glug/timer/continuous_timer.h>
#include <glug/timer/time_t.h>
#include <frac_t.h>
#include <defs.h>
#include <mocks/timer_bridge.h>
#include <mocks/allocator/counted.h>
#include <mocks/tick.h>

#include <stdlib.h>

static struct glug_icontinuous_timer icont;
static struct glug_continuous_timer *timer;

static struct glug_allocator allocator;

void before_each(void)
{
    memset(&icont, 0, sizeof(icont));

    CU_ASSERT_PTR_NULL_FATAL(icont.alloc);
    CU_ASSERT_PTR_NULL_FATAL(icont.free);

    CU_ASSERT_PTR_NULL_FATAL(icont.start);
    CU_ASSERT_PTR_NULL_FATAL(icont.pause);
    CU_ASSERT_PTR_NULL_FATAL(icont.reset);

    CU_ASSERT_PTR_NULL_FATAL(icont.delta);
    CU_ASSERT_PTR_NULL_FATAL(icont.run_time);

    CU_ASSERT_PTR_NULL_FATAL(icont.resolution);
    CU_ASSERT_PTR_NULL_FATAL(icont.state);

    glug_icontinuous_timer_init(&icont);

    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.alloc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.free);

    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.start);
    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.pause);
    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.reset);

    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.delta);
    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.run_time);

    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.resolution);
    CU_ASSERT_PTR_NOT_NULL_FATAL(icont.state);

    timer = NULL;

    allocator = get_counted_allocator();
    reset_alloc_count();
    reset_free_count();

    icont.alloc(&allocator, &timer);

    CU_ASSERT_PTR_NOT_NULL_FATAL(timer);

    uint64_t tick = 0;
    set_continuous_ticks(&tick);
    set_continuous_res(&(struct glug_time){ 0, 0 });
    set_continuous_scale(&(struct frac){ 1, 1 });
}

void after_each(void)
{
    icont.free(&timer);
}

void test_timer_alloc(void)
{
    CU_ASSERT_EQUAL(alloc_count(), 1);
    CU_ASSERT_EQUAL(free_count(), 0);
}

void test_timer_free(void)
{
    icont.free(&timer);

    CU_ASSERT_PTR_NULL(timer);
    CU_ASSERT_EQUAL(alloc_count(), 1);
    CU_ASSERT_EQUAL(free_count(), 1);

    // re-alloc the timer for the free in before_each
    icont.alloc(&allocator, &timer);
}

void test_timer_resolution(void)
{
    struct glug_time expected = { 2, 500 };
    set_continuous_res(&expected);

    struct glug_time actual;
    icont.resolution(&actual);

    assert_time_equal(&expected, &actual);
}

void test_stopped_timer(void)
{
    struct glug_time expected_delta = { 0, 0 }, expected_run = { 0, 0 };

    struct glug_time actual_delta;
    icont.delta(timer, &actual_delta);

    assert_time_equal(&expected_delta, &actual_delta);

    struct glug_time actual_run;
    icont.delta(timer, &actual_run);

    assert_time_equal(&expected_run, &actual_run);

    // start, pause, and reset the timer
    icont.start(timer);
    uint64_t ticks = 100;
    set_continuous_ticks(&ticks); // advance time a bit
    icont.pause(timer);

    icont.reset(timer);
    icont.delta(timer, &actual_delta);
    icont.run_time(timer, &actual_run);

    assert_time_equal(&expected_delta, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);
}

void test_running_timer(void)
{
    uint64_t ticks = 0;
    struct glug_time expected_delta = { 0, 0 }, expected_run = { 0, 0 };
    struct scale_args scale_args_delta, scale_args_run;

    // start the timer
    icont.start(timer);
    ticks = 2500;
    set_continuous_ticks(&ticks);

    struct glug_time actual_delta, actual_run;
    icont.delta(timer, &actual_delta);
    scale_args_delta = get_scale_last_args();
    icont.run_time(timer, &actual_run);
    scale_args_run = get_scale_last_args();

    expected_delta.nsec = (uint32_t)ticks;
    expected_run.nsec = (uint32_t)ticks;
    assert_time_equal(&expected_delta, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);

    // check the tick scaling function was called with the right args
    CU_ASSERT_EQUAL(expected_delta.nsec, scale_args_delta.ticks);
    assert_frac_equal(&(struct frac){ 1, 1 }, &scale_args_delta.scale);
    CU_ASSERT_EQUAL(expected_run.nsec, scale_args_run.ticks);
    assert_frac_equal(&(struct frac){ 1, 1 }, &scale_args_run.scale);

    // continue running and get totals again
    ticks = 70000;
    set_continuous_ticks(&ticks);

    icont.delta(timer, &actual_delta);
    scale_args_delta = get_scale_last_args();
    icont.run_time(timer, &actual_run);
    scale_args_run = get_scale_last_args();

    expected_delta.nsec = (uint32_t)(ticks - expected_delta.nsec);
    expected_run.nsec = (uint32_t)ticks;
    assert_time_equal(&expected_delta, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);

    // check the tick scaling function args again
    CU_ASSERT_EQUAL(expected_delta.nsec, scale_args_delta.ticks);
    assert_frac_equal(&(struct frac){ 1, 1 }, &scale_args_delta.scale);
    CU_ASSERT_EQUAL(expected_run.nsec, scale_args_run.ticks);
    assert_frac_equal(&(struct frac){ 1, 1 }, &scale_args_run.scale);

    // reset the timer without pausing
    ticks = 75000;
    set_continuous_ticks(&ticks);

    icont.reset(timer);
    ticks = 1000000;
    set_continuous_ticks(&ticks);

    icont.delta(timer, &actual_delta);
    icont.run_time(timer, &actual_run);

    expected_delta.nsec = (uint32_t)(ticks - 75000);
    expected_run.nsec = expected_delta.nsec;
    assert_time_equal(&expected_delta, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);
}

void test_paused_timer(void)
{
    uint64_t ticks = 0;
    struct glug_time expected_delta = { 0, 0 }, expected_run = { 0, 0 }, clear_time = { 0, 0 };

    // start and pause the timer
    icont.start(timer);
    ticks = 500; // advance time
    set_continuous_ticks(&ticks);
    icont.pause(timer);

    struct glug_time actual_delta, actual_run;
    icont.delta(timer, &actual_delta);
    icont.run_time(timer, &actual_run);

    expected_delta.nsec = (uint32_t)ticks;
    expected_run.nsec += (uint32_t)ticks;
    assert_time_equal(&expected_delta, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);

    // reading delta again will measure time since last read (while paused: 0) -- run time unchanged
    ticks = 1500; // advance time again
    set_continuous_ticks(&ticks);

    icont.delta(timer, &actual_delta);
    icont.run_time(timer, &actual_run);
    assert_time_equal(&clear_time, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);

    // starting the timer will not have an effect on the delta or run durations
    ticks = 2500; // advance time for the end of the pause
    set_continuous_ticks(&ticks);
    icont.start(timer);

    ticks = NSEC_PER_SEC + 3100; // advance by 1s + 600ns
    set_continuous_ticks(&ticks);

    icont.delta(timer, &actual_delta);
    icont.run_time(timer, &actual_run);

    expected_delta.nsec = 3100 - 2500;
    expected_delta.sec = 1;
    expected_run.nsec += 3100 - 2500;
    expected_run.sec += 1;
    assert_time_equal(&expected_delta, &actual_delta);
    assert_time_equal(&expected_run, &actual_run);
}

void test_timer_state(void)
{
    // starts stopped
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_stopped);

    // resetting while stopped -> stopped
    icont.reset(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_stopped);

    // pausing while stopped -> stopped
    icont.pause(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_stopped);

    // starting while stopped -> running
    icont.start(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_running);

    // starting while running -> running
    icont.start(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_running);

    // resetting while running -> running
    icont.reset(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_running);

    // pausing while running -> paused
    icont.pause(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_paused);

    // pausing while paused -> paused
    icont.pause(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_paused);

    // starting while paused -> running
    icont.start(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_running);

    // resetting while paused -> stopped
    icont.pause(timer);
    icont.reset(timer);
    CU_ASSERT_EQUAL(icont.state(timer), glug_ts_stopped);
}

void test_multiple_timers(void)
{
    struct glug_continuous_timer *timer2 = NULL;
    struct glug_time expected_delta1 = { 0, 0 }, expected_run1 = { 0, 0 };

    icont.alloc(&allocator, &timer2);

    icont.start(timer);

    uint64_t ticks = 100;
    set_continuous_ticks(&ticks);

    struct glug_time expected_delta2 = { 0, (uint32_t)ticks }, expected_run2 = { 0, (uint32_t)ticks };
    icont.start(timer2);

    struct glug_time actual_delta1, actual_run1, actual_delta2, actual_run2;

    ticks = 1100;
    set_continuous_ticks(&ticks);

    icont.delta(timer, &actual_delta1);
    icont.run_time(timer, &actual_run1);
    icont.delta(timer2, &actual_delta2);
    icont.run_time(timer2, &actual_run2);

    expected_delta1.nsec = (uint32_t)ticks;
    expected_run1.nsec   = (uint32_t)ticks;
    expected_delta2.nsec = (uint32_t)(ticks - expected_delta2.nsec);
    expected_run2.nsec   = (uint32_t)(ticks - expected_run2.nsec);
    assert_time_equal(&expected_delta1, &actual_delta1);
    assert_time_equal(&expected_run1, &actual_run1);
    assert_time_equal(&expected_delta2, &actual_delta2);
    assert_time_equal(&expected_run2, &actual_run2);
}

int main(void)
{
    CU_pSuite suite = create_suite("continuous_timer", before_each, after_each);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "alloc", test_timer_alloc);
    CU_add_test(suite, "free", test_timer_free);
    CU_add_test(suite, "read stopped timer", test_stopped_timer);
    CU_add_test(suite, "read paused timer", test_paused_timer);
    CU_add_test(suite, "read running timer", test_running_timer);
    CU_add_test(suite, "resolution", test_timer_resolution);
    CU_add_test(suite, "state", test_timer_state);
    CU_add_test(suite, "run multiple", test_multiple_timers);

    return run_tests(CU_BRM_VERBOSE);
}
