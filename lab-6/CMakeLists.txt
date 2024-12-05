cmake_minimum_required(VERSION 3.26)
project(lin_sys_calc C)

set(CMAKE_C_STANDARD 23)

set(LIB_PATH "/Users/vitalii/lib")

add_subdirectory(${LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(lin_sys_calc
        main.c)

target_link_libraries(lin_sys_calc PUBLIC
        err
        get
        math_ops)