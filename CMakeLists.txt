cmake_minimum_required(VERSION 3.23)
project(advanced_algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(advanced_algorithms
        TestRunner.cpp
        algorithms/BinarySundayPatternMatchingAlgorithm.cpp
        algorithms/BruteForcePatternMatchingAlgorithm.cpp
        algorithms/FSMPatternMatchingAlgorithm.cpp
        algorithms/GusfieldZPatternMatchingAlgorithm.cpp
        algorithms/KMPPatternMatchingAlgorithm.cpp
        algorithms/RabinKarpPatternMatchingAlgorithm.cpp
        algorithms/SundayPatternMatchingAlgorithm.cpp
        algorithms/WildcardBruteForcePatternMatchingAlgorithm.cpp
        algorithms/WildcardPatternMatchingAlgorithm.cpp
        algorithms/WildcardSundayPatternMatchingAlgorithm.cpp
        algorithms/TwoDimensionalRabinKarpPatternMatchingAlgorithm.cpp
        main.cpp
        )

target_include_directories(advanced_algorithms PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms)

message(WARNING ${SOURCES})

file(GLOB files "static_assets/*.txt")
foreach(file ${files})
    configure_file(${file}
            ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

