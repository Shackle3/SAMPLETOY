cmake_minimum_required(VERSION 3.27)
project(src C)

set(CMAKE_C_STANDARD 23)

add_executable(src main.c
        TestsSampletoy.cpp
        TestsSampletoy.h)
