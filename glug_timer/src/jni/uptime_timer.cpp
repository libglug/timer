#include "org_libglug_timer_UptimeTimer.h"

#include "jalloc_context_t.hpp"
#include <glug/timer/uptime_timer.h>
#include <glug/timer/time_t.h>

extern jmethodID allocator_malloc_field, allocator_free_field;
extern jfieldID time_sec_field, time_nsec_field;

static glug_uptime_timer *buffer_to_timer(JNIEnv *env, jobject timer_buff)
{
    return reinterpret_cast<glug_uptime_timer *>(env->GetDirectBufferAddress(timer_buff));
}

static void *allocator_malloc(size_t nbytes, void *context)
{
    jalloc_context *jcontext = reinterpret_cast<jalloc_context *>(context);
    JNIEnv *env = jcontext->env;
    jobject jallocator = jcontext->jallocator;

    // call Java to allocate a buffer
    jobject buffer = env->CallObjectMethod(jallocator, allocator_malloc_field, (jint)nbytes);

    jcontext->alloc_size = nbytes;
    // return the buffer as a "malloced" block
    return env->GetDirectBufferAddress(buffer);
}

static void allocator_free(void *block, void *context)
{
    jalloc_context *jcontext = reinterpret_cast<jalloc_context *>(context);
    JNIEnv *env = jcontext->env;
    jobject jallocator = jcontext->jallocator;

    // call Java to free the buffer
    env->CallVoidMethod(jallocator, allocator_free_field, env->NewDirectByteBuffer(block, jcontext->alloc_size));
}

jobject JNICALL Java_org_libglug_timer_UptimeTimer_alloc(JNIEnv *env, jobject /* this */, jobject jallocator)
{
    jalloc_context alloc_context =
    {
        env,
        jallocator,
        0
    };
    glug_allocator allocator =
    {
        allocator_malloc,
        allocator_free,
        &alloc_context
    };

    struct glug_uptime_timer *timer;
    glug_uptime_timer_alloc(&allocator, &timer);

    return env->NewDirectByteBuffer(timer, alloc_context.alloc_size);
}

void JNICALL Java_org_libglug_timer_UptimeTimer_free(JNIEnv *env, jobject /* this */, jobject timer_buff)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);
    glug_uptime_timer_free(&timer);
}

void JNICALL Java_org_libglug_timer_UptimeTimer_start(JNIEnv *env, jobject /* this */, jobject timer_buff)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);
    glug_uptime_timer_start(timer);
}

void JNICALL Java_org_libglug_timer_UptimeTimer_pause(JNIEnv *env, jobject /* this */, jobject timer_buff)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);
    glug_uptime_timer_pause(timer);
}

void JNICALL Java_org_libglug_timer_UptimeTimer_reset(JNIEnv *env, jobject /* this */, jobject timer_buff)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);
    glug_uptime_timer_reset(timer);
}

void JNICALL Java_org_libglug_timer_UptimeTimer_delta(JNIEnv *env, jobject /* this */, jobject timer_buff, jobject delta)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);

    glug_time time;
    glug_uptime_timer_delta(timer, &time);

    env->SetIntField(delta, time_sec_field, time.sec);
    env->SetIntField(delta, time_nsec_field, time.nsec);
}

void JNICALL Java_org_libglug_timer_UptimeTimer_runTime(JNIEnv *env, jobject /* this */, jobject timer_buff, jobject run)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);

    glug_time time;
    glug_uptime_timer_run_time(timer, &time);

    env->SetIntField(run, time_sec_field, time.sec);
    env->SetIntField(run, time_nsec_field, time.nsec);
}

jint JNICALL Java_org_libglug_timer_UptimeTimer_state(JNIEnv *env, jobject /* this */, jobject timer_buff)
{
    glug_uptime_timer *timer = buffer_to_timer(env, timer_buff);
    return static_cast<jint>(glug_uptime_timer_state(timer));
}

void JNICALL Java_org_libglug_timer_UptimeTimer_timerRes(JNIEnv *env, jclass /* this_class */, jobject res)
{
    glug_time time;
    glug_uptime_timer_resolution(&time);

    env->SetIntField(res, time_sec_field, time.sec);
    env->SetIntField(res, time_nsec_field, time.nsec);
}
