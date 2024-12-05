cmake_minimum_required(VERSION 3.26)
project(trig_func_table C)

set(CMAKE_C_STANDARD 23)

set(LIB_PATH "/Users/vitalii/lib")

add_subdirectory(${LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(trig_func_table main.c)

target_link_libraries(trig_func_table PUBLIC
        err
        get
        math_ops
        trig_ops)