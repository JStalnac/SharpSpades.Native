cmake_minimum_required(VERSION 3.10)

project(pyspades)

add_library(pyspades SHARED
    common_c.h
    constants_c.h
    vxl_c.cpp
    vxl_c.h
    world_c.cpp
    pyspades.h
)

set_target_properties(pyspades PROPERTIES PUBLIC_HEADER pyspades.h)
target_include_directories(pyspades PRIVATE .)
