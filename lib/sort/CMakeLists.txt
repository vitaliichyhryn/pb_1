add_library(sort STATIC
        sort.c
        sort.h)

target_link_libraries(sort PUBLIC str)

target_include_directories(sort PUBLIC .)