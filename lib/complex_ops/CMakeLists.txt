add_library(complex_ops STATIC
        complex_ops.c
        complex_ops.h)

target_include_directories(complex_ops PUBLIC .)