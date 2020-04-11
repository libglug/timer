project(example)
include(cmake/add_example.cmake)

set(LIB glug_timer)
find_package(${LIB} REQUIRED)
set(GLUG_TARGET_NAME ${LIB}_test)
set(GLUG_TARGET_NAME++ ${LIB}_test++)

set(INSTALL_PATH example)

add_example(
    TARGET_NAME
        ${GLUG_TARGET_NAME}
    SRC
        main.c
    LINK_LIBS
        ${LIB}
)

add_example(
    TARGET_NAME
        ${GLUG_TARGET_NAME++}
    INSTALL_PATH
        ${INSTALL_PATH}
    SRC
        main.cpp
        timer.hpp timer.cpp
    LINK_LIBS
        ${LIB}
)
