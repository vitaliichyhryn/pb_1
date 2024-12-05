cmake_minimum_required(VERSION 3.26)
project(root_find C)

set(CMAKE_C_STANDARD 23)

set(LIB_PATH "/Users/vitalii/lib")

add_subdirectory(${LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(root_find
        main.c
        funcs.h
        funcs.c)

target_link_libraries(root_find PUBLIC
        err
        get
        math_ops)