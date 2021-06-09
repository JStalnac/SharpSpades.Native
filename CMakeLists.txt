cmake_minimum_required(VERSION 3.10)

project(sharpspades)

add_library(sharpspades SHARED
    common_c.h
    constants_c.h
    vxl_c.cpp
    vxl_c.h
    world_c.cpp
    pyspades.h
)

set_target_properties(sharpspades PROPERTIES PUBLIC_HEADER pyspades.h)
target_include_directories(sharpspades PRIVATE .)
