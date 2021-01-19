set(
    JAVA_BINDINGS
    include/glug/timer/bindings/java/org/libglug/Allocator.java
    include/glug/timer/bindings/java/org/libglug/DefaultAllocator.java
    include/glug/timer/bindings/java/org/libglug/timer/ContinuousTimer.java
    include/glug/timer/bindings/java/org/libglug/timer/State.java
    include/glug/timer/bindings/java/org/libglug/timer/Time.java
    include/glug/timer/bindings/java/org/libglug/timer/UptimeTimer.java
)

set(
    JNI_SOURCE
    src/jni/continuous_timer.cpp
    src/jni/jalloc_context_t.hpp
    src/jni/jni_onload.cpp
    src/jni/org_libglug_timer_ContinuousTimer.h
    src/jni/org_libglug_timer_UptimeTimer.h
    src/jni/uptime_timer.cpp
)
