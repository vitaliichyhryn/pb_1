add_library(get STATIC
        get.c
        get.h)

target_link_libraries(get PUBLIC
        clr_stdin
        err
        str)

target_include_directories(get PUBLIC .)