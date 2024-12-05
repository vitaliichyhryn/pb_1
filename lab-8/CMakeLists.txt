cmake_minimum_required(VERSION 3.26)
project(imped_calc C)

set(CMAKE_C_STANDARD 23)

set(LIB_PATH "/Users/vitalii/lib")

add_subdirectory(${LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(imped_calc main.c)

target_link_libraries(imped_calc PUBLIC
        complex_ops
        err
        get
        math_ops)