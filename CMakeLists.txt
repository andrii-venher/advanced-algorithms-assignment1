cmake_minimum_required(VERSION 3.23)
project(advanced_algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(advanced_algorithms
        Helpers.h
        main.cpp
        PatternMatchingAlgorithms.h)
