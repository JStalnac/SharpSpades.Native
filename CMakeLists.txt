cmake_minimum_required(VERSION 3.10)

project(sharpspades)

add_library(sharpspades SHARED
    common_c.h
    constants_c.h
    world_c.c
    memory.h
    sharpspades.h
    libvxl.c
    libvxl.h
)

set_target_properties(sharpspades PROPERTIES PUBLIC_HEADER pyspades.h)
target_include_directories(sharpspades PRIVATE .)
