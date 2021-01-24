include(${CMAKE_CURRENT_LIST_DIR}/os.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/set_compilation_props.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/link_libs.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/set_export_defs.cmake)

function(add_gluglib)
    set(OPTIONS)
    set(SINGLE_VALS STATIC_BUILD TARGET_NAME)
    set(
        MULTI_VALS
            WIN32_SOURCE MACOS_SOURCE LINUX_SOURCE BSD_SOURCE
            WIN32_LIBS MACOS_LIBS LINUX_LIBS BSD_LIBS
    )
    cmake_parse_arguments(GLUG "${OPTIONS}" "${SINGLE_VALS}" "${MULTI_VALS}" ${ARGN})

    detect_os()

    # make a giant list of all source files added to the project
    list(
        APPEND
        ALL_SOURCE
        ${GLUG_WIN32_SOURCE}
        ${GLUG_MACOS_SOURCE}
        ${GLUG_LINUX_SOURCE}
        ${GLUG_BSD_SOURCE}
    )

    # create a list of this platform's sources
    if (GLUG_OS_WIN32)
        list(APPEND PLAT_SOURCE ${GLUG_WIN32_SOURCE})
    elseif (GLUG_OS_MACOS)
        list(APPEND PLAT_SOURCE ${GLUG_MACOS_SOURCE})
    elseif (GLUG_OS_LINUX)
        list(APPEND PLAT_SOURCE ${GLUG_LINUX_SOURCE})
    elseif (GLUG_OS_BSD)
        list(APPEND PLAT_SOURCE ${GLUG_BSD_SOURCE})
    endif()

    # remove the source files from the "all" list for the current platform
    list(REMOVE_ITEM ALL_SOURCE ${PLAT_SOURCE})

    # compile the sources for this platform only
    set_compilation_props("${ALL_SOURCE}" FALSE)
    set_compilation_props("${PLAT_SOURCE}" TRUE)

    # set the library type
    set(LIB_TYPE SHARED)
    if (GLUG_STATIC_BUILD)
        set(LIB_TYPE STATIC)
    endif()

    # create the library target
    add_library(${GLUG_TARGET_NAME} ${LIB_TYPE} ${ALL_SOURCE} ${PLAT_SOURCE})

    # set the defs for the target
    set(WINDEFS FALSE)
    if (GLUG_OS_WIN32)
        set(WINDEFS TRUE)
    endif()
    set_export_defs(${GLUG_TARGET_NAME} ${GLUG_STATIC_BUILD} ${WINDEFS})

    # link to other libraries
    if (GLUG_OS_WIN32)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_WIN32_LIBS}")
    elseif (GLUG_OS_MACOS)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_MACOS_LIBS}")
    elseif (GLUG_OS_LINUX)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_LINUX_LIBS}")
    elseif (GLUG_OS_BSD)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_BSD_LIBS}")
    endif()

endfunction()
