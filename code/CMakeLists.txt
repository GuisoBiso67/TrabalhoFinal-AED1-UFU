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
        cmake-build-debug/archives/profiles.txt
        cmake-build-debug/archives/s1.txt
        cmake-build-debug/archives/s2.txt
        cmake-build-debug/archives/s3.txt
        cmake-build-debug/archives/s4.txt
        cmake-build-debug/archives/s5.txt
        cmake-build-debug/archives/s6.txt
        cmake-build-debug/archives/s7.txt
        cmake-build-debug/archives/s8.txt)
