cmake_minimum_required(VERSION 3.23)
project(advanced_algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(advanced_algorithms
        TestRunner.h
        TestRunner.cpp
        main.cpp
        PatternMatchingAlgorithms.h)

file(GLOB files "static_assets/*.txt")
foreach(file ${files})
    configure_file(${file}
            ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

