add_library(math_ops STATIC
        math_ops.c
        math_ops.h)

target_link_libraries(math_ops PRIVATE err)

target_include_directories(math_ops PUBLIC .)