list(
    APPEND
    EXPECTED_DIRS
    cmake
    examples
    include
    lib
)

list(
    APPEND
    EXPECTED_INCLUDES
    allocator_t.h
    bool.h
    extern.h
    import.h
    os.h
    params.h
    std_allocator.inl
    timer.h
    timer
    timer/bindings
    timer/bindings/c++
    timer/bindings/c++/continuous_timer.hpp
    timer/bindings/c++/continuous_timer.inl
    timer/bindings/c++/uptime_timer.hpp
    timer/bindings/c++/uptime_timer.inl
    timer/continuous_timer.h
    timer/continuous_timer_t.h
    timer/time_t.h
    timer/timer_state.h
    timer/uptime_timer.h
    timer/uptime_timer_t.h
    timer/version.h
)

list(
    APPEND
    EXPECTED_EXAMPLES_WIN
    example-glug_timer.exe
    example-glug_timer_cpp.exe
)

list(
    APPEND
    EXPECTED_EXAMPLES_NIX
    example-glug_timer
    example-glug_timer_cpp
)

list(
    APPEND
    EXPECTED_LIBS_WIN_MSVC
    glug_timer.dll
    glug_timer.lib
)

list(
    APPEND
    EXPECTED_LIBS_WIN_MINGW
    libglug_timer.dll
    libglug_timer.dll.a
)

list(
    APPEND
    EXPECTED_LIBS_MAC
    libglug_timer.dylib
)

list(
    APPEND
    EXPECTED_LIBS_BSD_LIN
    libglug_timer.so
)

list(
    APPEND
    EXPECTED_EXPORTS_DEBUG
    Find-glug_timer.cmake
    Find-glug_timer-debug.cmake
)

list(
    APPEND
    EXPECTED_EXPORTS_RELEASE
    Find-glug_timer.cmake
    Find-glug_timer-release.cmake
)

