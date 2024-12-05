add_library(rand STATIC
        rand.c
        rand.h)

target_include_directories(rand PUBLIC .)