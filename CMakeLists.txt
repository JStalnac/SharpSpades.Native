cmake_minimum_required(VERSION 3.10)

project(sharpspades)

add_library(sharpspades SHARED
    sharpspades.h
    libmapvxl.c
    libmapvxl.h
    line.c
    hitdetection.c
    types.h
    player.c
    grenade.c
    memory.c
)

add_compile_options(-Wall -Wextra -Wpedantic -O2)

set_target_properties(sharpspades PROPERTIES PUBLIC_HEADER sharpspades.h)
target_include_directories(sharpspades PUBLIC .)
