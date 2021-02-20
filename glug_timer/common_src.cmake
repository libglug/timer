set(
    COMMON_SOURCE
    common_headers/include/glug/allocator_t.h
    common_headers/include/glug/std_allocator.inl
    common_headers/include/glug/bool.h
    common_headers/include/glug/extern.h
    common_headers/include/glug/import.h
    common_headers/include/glug/os.h
    common_headers/include/glug/params.h

    include/glug/timer.h
    include/glug/timer/version.h.in
    include/glug/timer/continuous_timer.h
    include/glug/timer/uptime_timer.h
    include/glug/timer/continuous_timer_t.h
    include/glug/timer/uptime_timer_t.h
    include/glug/timer/time_t.h
    include/glug/timer/timer_state.h

    src/timer.h
    src/timer.c
    src/continuous_timer.c
    src/uptime_timer.c
    src/frac_t.h
    src/timer_bridge.h
    src/tick.h
    src/tick.c
    src/defs.h
)

set(
    BINDINGS
    include/glug/timer/bindings/c++/continuous_timer.hpp
    include/glug/timer/bindings/c++/continuous_timer.inl
    include/glug/timer/bindings/c++/uptime_timer.hpp
    include/glug/timer/bindings/c++/uptime_timer.inl
)
