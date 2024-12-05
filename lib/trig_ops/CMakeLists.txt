add_library(trig_ops STATIC
        trig_ops.c
        trig_ops.h)

target_link_libraries(trig_ops PUBLIC err)

target_include_directories(trig_ops PUBLIC .)