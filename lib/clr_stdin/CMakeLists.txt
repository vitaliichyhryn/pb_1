add_library(clr_stdin STATIC
        clr_stdin.c
        clr_stdin.h)

target_include_directories(clr_stdin PUBLIC .)