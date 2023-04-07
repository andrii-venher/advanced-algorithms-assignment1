#ifndef ADVANCED_ALGORITHMS_HELPERS_H
#define ADVANCED_ALGORITHMS_HELPERS_H

#include <iostream>
#include <chrono>
#include <fstream>
#include "PatternMatchingAlgorithms.h"

void test_algorithm(PatternMatchingAlgorithm *algorithm, const std::string &t, const std::string &p) {
    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;
    int times = 1000;
    ns total_time_taken = ns(0);

    int matches;

    for (size_t i = 0; i < times; ++i) {
        auto start = clock::now();
        matches = algorithm->findMatches(t, p);
        auto end = clock::now();
        total_time_taken += std::chrono::duration_cast<ns>(end - start);
    }

    std::cout << algorithm->getName() << " (matches: " << matches << "): " << total_time_taken.count() / times / 1000
              << "ms\n";
}

std::string txt_to_string(std::string filename) {
    std::string tmp;
    std::string file_text;
    std::ifstream file_in;

    file_in.open(filename);
    while (getline(file_in, tmp)) {
        file_text += tmp += '\n';
    }
    file_text.pop_back();
    file_in.close();

    return file_text;
}

#endif //ADVANCED_ALGORITHMS_HELPERS_H
