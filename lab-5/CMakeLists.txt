cmake_minimum_required(VERSION 3.26)
project(sort_strs C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug)

set(LIB_PATH "/Users/vitalii/lib")

add_subdirectory(${LIB_PATH} ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(sort_strs main.c)

target_link_libraries(sort_strs PUBLIC
        err
        get
        math_ops
        rand
        sort)

target_compile_options(sort_strs PRIVATE -fsanitize=address)
target_link_options(sort_strs PRIVATE -fsanitize=address)