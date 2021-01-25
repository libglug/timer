add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cunit/CUnit EXCLUDE_FROM_ALL)
include(${CMAKE_CURRENT_LIST_DIR}/add_unit_test.cmake)

find_package(glug_timer REQUIRED)

set(LIB_SRC_ROOT ${CMAKE_SOURCE_DIR}/glug_timer/src)
set(LIB_INC_ROOT ${CMAKE_SOURCE_DIR}/glug_timer/include)

function(add_test_by_conf TEST_ROOT TEST_CONF)
    include(${TEST_ROOT}/${TEST_CONF})
    set(TEST_TARGET "test-${TEST_TARGET}")

    list(
        TRANSFORM
            TEST_SOURCE
        PREPEND
            ${TEST_ROOT}/
    )

    list(
        TRANSFORM
            TEST_LIB_SOURCE
        PREPEND
            ${LIB_SRC_ROOT}/
    )

    list(
        TRANSFORM
            TEST_MOCK_SOURCE
        PREPEND
            ${TEST_ROOT}/utils/
    )

    add_unit_test(
        TARGET
            ${TEST_TARGET}
        SOURCES
            ${TEST_SOURCE}
            ${TEST_LIB_SOURCE}
            ${TEST_MOCK_SOURCE}
            ${TEST_ROOT}/utils/suites/create_suite.h
            ${TEST_ROOT}/utils/suites/create_suite.c
            ${TEST_ROOT}/utils/asserts/time.h
            ${TEST_ROOT}/utils/asserts/time.c
            ${TEST_ROOT}/utils/asserts/frac.h
            ${TEST_ROOT}/utils/asserts/frac.c
            ${TEST_ROOT}/utils/asserts/clocktime.h
            ${TEST_ROOT}/utils/asserts/clocktime.c
        INCLUDE_DIRS
            ${TEST_ROOT}/utils
            ${TEST_ROOT}/utils/mocks
            ${LIB_SRC_ROOT}
            ${LIB_INC_ROOT}
            ${TEST_INCLUDE_DIRS}
    )

    foreach(DEF IN LISTS TEST_DEFS)
        target_compile_definitions(
            ${TEST_TARGET}
            PRIVATE
                ${DEF}
        )
    endforeach()

    foreach(MOCK IN LISTS TEST_MOCKS)
        target_compile_definitions(
            ${TEST_TARGET}
            PRIVATE
                ${MOCK}=${MOCK}_mocked
        )
    endforeach()

    list(
        APPEND
        TEST_TARGETS
        ${TEST_TARGET}
    )

    set(TEST_TARGETS ${TEST_TARGETS} PARENT_SCOPE)

endfunction()

# unit tests
list(
    APPEND
    TEST_TARGETS
)

add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/tick.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/qpc.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/quit.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/mach.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/clock-linux.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/clock-bsd.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/bridge-win32.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/bridge-osx.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/bridge-linux.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/bridge-bsd.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/timer-continuous.cmake)
add_test_by_conf(${CMAKE_CURRENT_LIST_DIR} confs/timer-uptime.cmake)

foreach(TEST_TARGET IN LISTS TEST_TARGETS)
    add_custom_command(
        TARGET
            ${TEST_TARGET} POST_BUILD
        # copy the CUnit library to the same directory as the test binaries
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:CUnit> $<TARGET_FILE_DIR:${TEST_TARGET}>
    )
endforeach()
