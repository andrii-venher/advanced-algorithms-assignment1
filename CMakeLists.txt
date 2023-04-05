cmake_minimum_required(VERSION 3.23)
project(advanced_algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(advanced_algorithms
        Helpers.h
        main.cpp
        PatternMatchingAlgorithms.h)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/large_pattern.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/small_pattern.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/text.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)