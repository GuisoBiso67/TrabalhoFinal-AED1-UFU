cmake_minimum_required(VERSION 3.31)
project(code C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(code
        f-series.c
        f-series.h
        main.c)
