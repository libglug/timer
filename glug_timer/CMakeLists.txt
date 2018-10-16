include(${PROJECT_SOURCE_DIR}/cmake/macros/add_gluglib.cmake)

set(SRC_ROOT src)
set(INC_ROOT include/glug)

list(
    APPEND
    COMMON_SOURCE
    ${INC_ROOT}/timer.h
    ${INC_ROOT}/timer/time.h
    ${INC_ROOT}/timer/time_t.h
    ${INC_ROOT}/timer/timer.h
    ${INC_ROOT}/timer/timer_state.h
    ${SRC_ROOT}/time.c
    ${SRC_ROOT}/timer.h
    ${SRC_ROOT}/timer.c
    ${SRC_ROOT}/timer_platform.h
    # add common source files
)

set(WIN32_ROOT ${SRC_ROOT}/win32)
list(
    APPEND
    WIN32_SOURCE
    ${COMMON_SOURCE}
    ${WIN32_ROOT}/win32_timer.c
)

set(MACOS_ROOT ${SRC_ROOT}/macos)
list(
    APPEND
    MACOS_SOURCE
    ${COMMON_SOURCE}
    ${MACOS_ROOT}/macos_timer.c
)

set(LINUX_ROOT ${SRC_ROOT}/linux)
list(
    APPEND
    LINUX_SOURCE
    ${COMMON_SOURCE}
    ${LINUX_ROOT}/linux_timer.c
)

set(GLUG_TARGET_NAME ${CMAKE_PROJECT_NAME})

add_gluglib(
    TARGET_NAME ${GLUG_TARGET_NAME}
    WIN32_SOURCE ${WIN32_SOURCE}
    MACOS_SOURCE ${MACOS_SOURCE}
    LINUX_SOURCE ${LINUX_SOURCE}
)

# install the library
install(
    TARGETS ${GLUG_TARGET_NAME}
    DESTINATION ${GLUG_DIST_LIBR_DIR}
)

install(
    TARGETS ${GLUG_TARGET_NAME}
    DESTINATION ${GLUG_DIST_XMPL_DIR}
)
