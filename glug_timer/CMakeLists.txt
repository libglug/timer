cmake_minimum_required(VERSION 3.0)

set(VER_MAJOR 1)
set(VER_MINOR 0)
set(VER_PATCH 0)
project({LIB_NAME} VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})
include(cmake/add_gluglib.cmake)

option(BUILD_STATIC "Build as a static library instead of shared" OFF)

set(COM_ROOT common_headers/include/glug)
set(SRC_ROOT src)
set(INC_ROOT include/glug)

list(
    APPEND
    COMMON_SOURCE
    ${COM_ROOT}/allocator_t.h
    ${COM_ROOT}/bool.h
    ${COM_ROOT}/extern.h
    ${COM_ROOT}/import.h
    ${COM_ROOT}/namespace.h
    ${COM_ROOT}/os.h
    ${COM_ROOT}/params.h
    ${INC_ROOT}/timer.h
    ${INC_ROOT}/timer/time_t.h
    ${INC_ROOT}/timer/timer_t.h
    ${INC_ROOT}/timer/timer.h
    ${INC_ROOT}/timer/timer_state.h
    ${SRC_ROOT}/timer.h
    ${SRC_ROOT}/timer.c
    ${SRC_ROOT}/timer_platform.h
    ${SRC_ROOT}/safe_clock_scale.c
)

# Windows sources
list(
    APPEND
    WIN32_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/win32/win32_timer.c
)

# Mac OS sources
list(
    APPEND
    MACOS_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/macos/macos_timer.c
)

# linux sources
list(
    APPEND
    LINUX_SOURCE
    ${COMMON_SOURCE}
    ${SRC_ROOT}/linux/linux_timer.c
)

add_gluglib(
    TARGET_NAME ${CMAKE_PROJECT_NAME}
    STATIC_BUILD ${BUILD_STATIC}
    WIN32_SOURCE ${WIN32_SOURCE}
    MACOS_SOURCE ${MACOS_SOURCE}
    LINUX_SOURCE ${LINUX_SOURCE}
    WIN32_LIBS
    MACOS_LIBS
    LINUX_LIBS
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common_headers/include>
    INTERFACE
        $<INSTALL_INTERFACE:include>
)

# install the library
install(
    TARGETS
        ${CMAKE_PROJECT_NAME}
    EXPORT
        Find${CMAKE_PROJECT_NAME}
    DESTINATION
        lib
)

#install the lib's headers
install(
    DIRECTORY
        include/
    DESTINATION
        include
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
export(PACKAGE ${CMAKE_PROJECT_NAME})
export(
    TARGETS
        ${CMAKE_PROJECT_NAME}
    FILE
        ${CMAKE_PROJECT_NAME}-config.cmake
)

# install export file
install(
    EXPORT
        Find${CMAKE_PROJECT_NAME}
    DESTINATION
        cmake
)
