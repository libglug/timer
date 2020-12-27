add_subdirectory(cunit/CUnit EXCLUDE_FROM_ALL)
include(add_unit_test.cmake)

set(TESTED_LIB glug_timer)

set(LIB_SRC_ROOT ${CMAKE_SOURCE_DIR}/${TESTED_LIB}/src)
set(LIB_INC_ROOT ${CMAKE_SOURCE_DIR}/${TESTED_LIB}/include)

macro(add_test_by_conf TEST_CONF)
    include(${TEST_CONF})

    list(
        TRANSFORM
            TEST_LIB_SOURCE
        PREPEND
            ${LIB_SRC_ROOT}/
    )

    add_unit_test(
        TARGET
            ${TEST_TARGET}
        SOURCES
            ${TEST_SOURCE}
            ${TEST_LIB_SOURCE}
            test_utils/suites/create_suite.h
            test_utils/suites/create_suite.c
            test_utils/asserts/time.h
            test_utils/asserts/time.c
        INCLUDE_DIRS
            test_utils
            ${LIB_SRC_ROOT}
            ${LIB_INC_ROOT}
            ${TEST_INCLUDE_DIRS}
    )

    list(
        APPEND
        TEST_TARGETS
        ${TEST_TARGET}
    )

endmacro()

# unit tests
list(
    APPEND
    TEST_TARGETS
)

add_test_by_conf("tick.cmake")

# copy the executable to this build directory (MSVC likes to hide it in Debug/Release folders)
add_custom_target(
    check
    ALL
    DEPENDS
        CUnit ${TEST_TARGETS} ${TESTED_LIB}
)

add_custom_command(
    TARGET
        check POST_BUILD
    # copy the CUnit library to the same directory as the test binaries
    COMMAND
        ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:CUnit> ${CMAKE_CURRENT_BINARY_DIR}
#    TODO: for integration or e2e test
#    # copy the library to the same directory as the test binaries
#    COMMAND
#        ${CMAKE_COMMAND} -E copy
#            $<TARGET_FILE:${TESTED_LIB}> ${CMAKE_CURRENT_BINARY_DIR}
)
