cmake_minimum_required(VERSION 3.7)
project(decoder)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c Generator.h Generator.c)
add_executable(decoder ${SOURCE_FILES})