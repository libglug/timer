add_subdirectory(cunit/CUnit EXCLUDE_FROM_ALL)
include(add_unit_test.cmake)

set(TESTED_LIB glug_timer)
find_package(${TESTED_LIB} REQUIRED)

set(LIB_SRC_ROOT ${CMAKE_SOURCE_DIR}/${TESTED_LIB}/src)
set(LIB_INC_ROOT ${CMAKE_SOURCE_DIR}/${TESTED_LIB}/include)

function(add_test_by_conf TEST_CONF)
    include(${TEST_CONF})
    set(TEST_TARGET "test-${TEST_TARGET}")

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
            test_utils/
    )

    add_unit_test(
        TARGET
            ${TEST_TARGET}
        SOURCES
            ${TEST_SOURCE}
            ${TEST_LIB_SOURCE}
            ${TEST_MOCK_SOURCE}
            test_utils/suites/create_suite.h
            test_utils/suites/create_suite.c
            test_utils/asserts/time.h
            test_utils/asserts/time.c
            test_utils/asserts/frac.h
            test_utils/asserts/frac.c
            test_utils/asserts/clocktime.h
            test_utils/asserts/clocktime.c
        INCLUDE_DIRS
            test_utils
            test_utils/mocks
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

add_test_by_conf("tick.cmake")
add_test_by_conf("qpc.cmake")
add_test_by_conf("quit.cmake")
add_test_by_conf("mach.cmake")
add_test_by_conf("clock-linux.cmake")
add_test_by_conf("clock-bsd.cmake")
add_test_by_conf("bridge-win32.cmake")
add_test_by_conf("bridge-osx.cmake")
add_test_by_conf("bridge-linux.cmake")
add_test_by_conf("bridge-bsd.cmake")
add_test_by_conf("timer-continuous.cmake")
add_test_by_conf("timer-uptime.cmake")

# build all tests suites as part of the "check" target
add_custom_target(
    check
    ALL
    DEPENDS
        CUnit ${TEST_TARGETS} ${TESTED_LIB}
)
foreach(TEST_TARGET IN LISTS TEST_TARGETS)
    add_custom_command(
        TARGET
            check POST_BUILD
        # copy the CUnit library to the same directory as the test binaries
        COMMAND
            ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:CUnit> $<TARGET_FILE_DIR:${TEST_TARGET}>
    )
endforeach()
