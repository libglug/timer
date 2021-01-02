project(example)
include(cmake/add_example.cmake)

set(LIB glug_timer)
find_package(${LIB} REQUIRED)
set(GLUG_TARGET_NAME ${LIB}_ex)
set(GLUG_TARGET_NAME++ ${LIB}_ex_cpp)

set(INSTALL_PATH example)

add_example(
    TARGET_NAME
        ${GLUG_TARGET_NAME}
    INSTALL_PATH
        ${INSTALL_PATH}
    SRC
        c/main.c
    LINK_LIBS
        ${LIB}
)

add_example(
    TARGET_NAME
        ${GLUG_TARGET_NAME++}
    INSTALL_PATH
        ${INSTALL_PATH}
    SRC
        c++/main.cpp
        c++/timer.hpp c++/timer.cpp
    LINK_LIBS
        ${LIB}
)

target_compile_features(
    ${GLUG_TARGET_NAME++}
    PUBLIC
        cxx_std_11
)
set_target_properties(
    ${GLUG_TARGET_NAME++}
    PROPERTIES
        CXX_EXTENSIONS OFF
)
