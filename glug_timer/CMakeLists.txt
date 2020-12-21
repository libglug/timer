cmake_minimum_required(VERSION 3.0)

include(cmake/version.cmake)

parse_git_tag_version("VER_MAJOR" "VER_MINOR" "VER_PATCH" "VER_META" "VER_REV" "VER_HASH" "VER_FULL")
set(FULL_VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}-${VER_META}")

project(
    glug_timer
    LANGUAGES
        C
    VERSION
        ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}
)

include(cmake/add_gluglib.cmake)

option(BUILD_STATIC "Build as a static library instead of shared?" OFF)

set(COM_ROOT common_headers/include/glug)
set(SRC_ROOT src)
set(INC_ROOT include/glug)

# configure files
set(CONFIGURED_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/configured)
configure_file(${INC_ROOT}/timer/version.h.in ${CONFIGURED_OUT_DIR}/include/glug/timer/version.h)

list(
    APPEND
    COMMON_SOURCE
    ${COM_ROOT}/allocator_t.h
    ${COM_ROOT}/bool.h
    ${COM_ROOT}/extern.h
    ${COM_ROOT}/import.h
    ${COM_ROOT}/os.h
    ${COM_ROOT}/params.h
    ${INC_ROOT}/timer.h
    ${INC_ROOT}/timer/version.h.in
    ${INC_ROOT}/timer/continuous_timer.h
    ${INC_ROOT}/timer/uptime_timer.h
    ${INC_ROOT}/timer/continuous_timer_t.h
    ${INC_ROOT}/timer/uptime_timer_t.h
    ${INC_ROOT}/timer/time_t.h
    ${INC_ROOT}/timer/timer_state.h
    ${SRC_ROOT}/timer.h
    ${SRC_ROOT}/timer.c
    ${SRC_ROOT}/continuous_timer.c
    ${SRC_ROOT}/uptime_timer.c
    ${SRC_ROOT}/frac.h
    ${SRC_ROOT}/timer_bridge.h
    ${SRC_ROOT}/tick.h
    ${SRC_ROOT}/tick.c
    ${SRC_ROOT}/defs.h
)

# Windows sources
list(
    APPEND
    WIN32_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/timer_bridge_win32.c
    ${SRC_ROOT}/qpc/qpc.h
    ${SRC_ROOT}/qpc/qpc.c
    ${SRC_ROOT}/qpc/quit.h
    ${SRC_ROOT}/qpc/quit.c
)

# Mac OS sources
list(
    APPEND
    MACOS_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/timer_bridge_macos.c
    ${SRC_ROOT}/mach/mach.h
    ${SRC_ROOT}/mach/mach.c
)

# linux sources
list(
    APPEND
    LINUX_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/timer_bridge_linux.c
    ${SRC_ROOT}/clock/clock.h
    ${SRC_ROOT}/clock/clock.c
)

#bsd sources
list(
    APPEND
    BSD_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/timer_bridge_bsd.c
    ${SRC_ROOT}/clock/clock.h
    ${SRC_ROOT}/clock/clock.c
)

add_gluglib(
    TARGET_NAME
        ${PROJECT_NAME}
    STATIC_BUILD
        ${BUILD_STATIC}
    WIN32_SOURCE
        ${WIN32_SOURCE}
    MACOS_SOURCE
        ${MACOS_SOURCE}
    LINUX_SOURCE
        ${LINUX_SOURCE}
    BSD_SOURCE
        ${BSD_SOURCE}
    WIN32_LIBS
    MACOS_LIBS
    LINUX_LIBS
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
        _WIN32_WINNT=0x0601
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CONFIGURED_OUT_DIR}/include> # because "version.h" is a configured file
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common_headers/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    INTERFACE
        $<INSTALL_INTERFACE:include>
)

# install the library
install(
    TARGETS
        ${PROJECT_NAME}
    EXPORT
        Find${PROJECT_NAME}
    DESTINATION
        lib
)

# install the lib's headers
install(
    DIRECTORY
        include/
    DESTINATION
        include
    FILES_MATCHING PATTERN
        "*.h"
)

# install the lib's configured version file
install(
    FILES
        ${CONFIGURED_OUT_DIR}/include/glug/timer/version.h
    DESTINATION
        include/glug/timer
)

# install the common_headers
install(
    DIRECTORY
        common_headers/include/
    DESTINATION
        include
    FILES_MATCHING PATTERN
        "*.h"
)

# export the package to be included in other projects
export(PACKAGE ${PROJECT_NAME})
export(
    TARGETS
        ${PROJECT_NAME}
    FILE
        ${PROJECT_NAME}-config.cmake
)

# install export file
install(
    EXPORT
        Find${PROJECT_NAME}
    DESTINATION
        cmake
)
