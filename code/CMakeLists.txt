cmake_minimum_required(VERSION 3.31)
project(code C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(code
        perfis.c
        perfis.h
        main.c
        series.c
        series.h
        cmake-build-debug/profiles.txt)
