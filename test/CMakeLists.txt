add_subdirectory(cunit/CUnit EXCLUDE_FROM_ALL)
include(add_unit_test.cmake)

set(TESTED_LIB glug_timer)
set(TEST_ROOT .)
set(LIB_SRC ../${TESTED_LIB}/src)
set(LIB_INC ../${TESTED_LIB}/include)

# unit tests
list(
    APPEND
    TEST_TARGETS
)

add_unit_test(
    TARGET
        tick-scale
    SOURCES
        ${LIB_SRC}/tick.h
        ${LIB_SRC}/tick.c
        suites/unit/tick.c
        suites/asserts.h
        suites/asserts.c
    INCLUDE_DIRS
        ${LIB_SRC}
        ${LIB_INC}
)

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
