cmake_minimum_required(VERSION 3.26)
project(sort_float_arr C)

set(CMAKE_C_STANDARD 23)

set(LIB_PATH "/Users/vitalii/lib")

add_subdirectory(${LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(sort_float_arr main.c
)

target_link_libraries(sort_float_arr PUBLIC
        err
        get
        math_ops
        rand
        sort)