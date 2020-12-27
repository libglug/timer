function(add_unit_test)
    set(SINGLE_VALS TARGET)
    set(MULTI_VALS SOURCES INCLUDE_DIRS)
    cmake_parse_arguments(UT "" "${SINGLE_VALS}" "${MULTI_VALS}" "${ARGN}")

    add_executable(
        ${UT_TARGET}
        ${UT_SOURCES}
    )

    target_include_directories(
        ${UT_TARGET}
        PRIVATE
            ${TEST_ROOT}
            ${SRC_ROOT}
            ${UT_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${UT_TARGET}
        CUnit
    )

    target_compile_definitions(
        ${UT_TARGET}
        PRIVATE
            GLUG_LIB_LOCAL=
            GLUG_LIB_API=
    )
    add_test(${UT_TARGET} ${UT_TARGET})
endfunction()
