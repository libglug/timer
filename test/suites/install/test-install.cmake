function(test_lists_equal ACTUAL EXPECTED ERROR_VARIABLE)
    list(FILTER ${ACTUAL} EXCLUDE REGEX .DS_Store)
    # test the lists are of equal length
    list(LENGTH ${ACTUAL} N_ACTUAL)
    list(LENGTH ${EXPECTED} N_EXPECTED)
    if (NOT ${N_ACTUAL} EQUAL ${N_EXPECTED})
        set(
            ${ERROR_VARIABLE}
            "expected ${N_EXPECTED}; got ${N_ACTUAL}\n actual: ${${ACTUAL}}\n expected: ${${EXPECTED}}"
            PARENT_SCOPE
        )
    endif()

    # test the lists have the same elements
    foreach(ITEM IN LISTS ${EXPECTED})
        list(FIND ${ACTUAL} ${ITEM} ITEM_INDEX)
        if (${ITEM_INDEX} EQUAL -1)
            set(
                ${ERROR_VARIABLE}
                "didn't find ${ITEM}"
                PARENT_SCOPE
            )
            break()
        endif()
        list(REMOVE_AT ${ACTUAL} ${ITEM_INDEX})
    endforeach()

endfunction()

message("Suite: verify installation")
include(${CHECK_FILE})

# check that the install directory exists
if (NOT EXISTS ${INSTALL_DIR})
    message(
        FATAL_ERROR
        "Could not find install directory: ${INSTALL_DIR}\n"
        "Did you run `cmake build <path> --target install install-examples`?"
    )
endif()

# test the root install directory
execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "  Test: install correct root dirs ...")
file(
    GLOB
    ROOT_DIRS
    RELATIVE
        ${INSTALL_DIR}
    ${INSTALL_DIR}/*
)

test_lists_equal(ROOT_DIRS EXPECTED_DIRS ERROR)
if (ERROR)
    execute_process(COMMAND ${CMAKE_COMMAND} -E echo "failed")
    message(
        FATAL_ERROR
        "Root directories are not equal\n"
        "${ERROR}"
    )
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "passed")

# test the includes
execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "  Test: install correct includes ...")
file(
    GLOB_RECURSE
    INCLUDES
    LIST_DIRECTORIES
        TRUE
    RELATIVE
        ${INSTALL_DIR}/include/glug
    ${INSTALL_DIR}/include/glug/*
)

test_lists_equal(INCLUDES EXPECTED_INCLUDES ERROR)
if (ERROR)
    execute_process(COMMAND ${CMAKE_COMMAND} -E echo "failed")
    message(
        FATAL_ERROR
        "includes are not equal\n"
        "${ERROR}"
    )
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "passed")

# test the examples
execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "  Test: install correct examples ...")
file(
    GLOB_RECURSE
    EXAMPLES
    LIST_DIRECTORIES
        TRUE
    RELATIVE
        ${INSTALL_DIR}/examples
    ${INSTALL_DIR}/examples/*
)

if ("${SYSTEM}" STREQUAL "Windows")

    test_lists_equal(EXAMPLES EXPECTED_EXAMPLES_WIN ERROR)

elseif ("${SYSTEM}" STREQUAL "Darwin" OR
        "${SYSTEM}" STREQUAL "Linux" OR
        "${SYSTEM}" STREQUAL "FreeBSD" OR
        "${SYSTEM}" STREQUAL "OpenBSD")

    test_lists_equal(EXAMPLES EXPECTED_EXAMPLES_NIX ERROR)

endif()

if (ERROR)
    execute_process(COMMAND ${CMAKE_COMMAND} -E echo "failed")
    message(
        FATAL_ERROR
        "examples are not equal\n"
        "${ERROR}"
    )
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "passed")

# test the libs
execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "  Test: install correct libs ...")
file(
    GLOB_RECURSE
    LIBS
    LIST_DIRECTORIES
        TRUE
    RELATIVE
        ${INSTALL_DIR}/lib
    ${INSTALL_DIR}/lib/*
)

if ("${SYSTEM}" STREQUAL "Windows")
    test_lists_equal(LIBS EXPECTED_LIBS_WIN_MSVC ERROR)

    if (ERROR)
        test_lists_equal(LIBS EXPECTED_LIBS_WIN_MINGW ERROR_GCC)
        if (NOT ERROR_GCC)
            unset(ERROR)
        endif()
        if (ERROR_GCC)
            execute_process(COMMAND ${CMAKE_COMMAND} -E echo "failed")
            message(
                FATAL_ERROR
                "libs are not equal\n"
                "${ERROR_GCC}\n"
                "--- OR ---\n"
                "${ERROR}"
            )
        endif()
    endif()

else ()
    if ("${SYSTEM}" STREQUAL "Darwin")

        test_lists_equal(LIBS EXPECTED_LIBS_MAC ERROR)

    elseif ("${SYSTEM}" STREQUAL "Linux" OR
            "${SYSTEM}" STREQUAL "FreeBSD" OR
            "${SYSTEM}" STREQUAL "OpenBSD")

        test_lists_equal(LIBS EXPECTED_LIBS_BSD_LIN ERROR)

    endif()

    if (ERROR)
        execute_process(COMMAND ${CMAKE_COMMAND} -E echo "failed")
        message(
            FATAL_ERROR
            "libs are not equal\n"
            "${ERROR}"
        )
    endif()
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "passed")

# test the exports
# TODO: pass in the build type to properly verify the exports (only supports debug and rel builds)
execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "  Test: install correct exports ...")
file(
    GLOB_RECURSE
    EXPORTS
    LIST_DIRECTORIES
        TRUE
    RELATIVE
        ${INSTALL_DIR}/cmake
    ${INSTALL_DIR}/cmake/*
)

test_lists_equal(EXPORTS EXPECTED_EXPORTS_DEBUG ERROR_DBG)
if (ERROR_DBG)
    test_lists_equal(EXPORTS EXPECTED_EXPORTS_RELEASE ERROR_REL)
    if (NOT ERROR_REL)
        unset(ERROR_DBG)
    endif()

    if (ERROR_REL)
        execute_process(COMMAND ${CMAKE_COMMAND} -E echo "failed")
        message(
            FATAL_ERROR
            "exports are not equal\n"
            "${ERROR_REL}\n"
            "--- OR ---\n"
            "${ERROR_DBG}"
        )
    endif()
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "passed")
