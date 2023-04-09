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

void test_algorithm_step(PatternMatchingAlgorithm *algorithm, const std::string &t, const std::string &small_p, const std::string &large_p) {
    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;
    ns small_total_time_taken;
    ns large_total_time_taken;
    int times = 100;
    int step = 1000;

    std::ofstream small_p_file;
    std::ofstream large_p_file;
    small_p_file.open(algorithm->getName() + "(small_pattern).txt");
    large_p_file.open(algorithm->getName() + "(large_pattern).txt");

    for (int size = step; size <= t.size(); size += step)
    {
        std::string part_of_t = t.substr(0, size);
        small_total_time_taken = ns(0);
        large_total_time_taken = ns(0);

        for (size_t time = 0; time < times; ++time) {
            auto start = clock::now();
            algorithm->findMatches(part_of_t, small_p);
            auto end = clock::now();
            small_total_time_taken += std::chrono::duration_cast<ns>(end - start);
        }

        for (size_t time = 0; time < times; ++time) {
            auto start = clock::now();
            algorithm->findMatches(part_of_t, large_p);
            auto end = clock::now();
            large_total_time_taken += std::chrono::duration_cast<ns>(end - start);
        }

        small_p_file << size << ' ' << small_total_time_taken.count() / times << std::endl;
        large_p_file << size << ' ' << large_total_time_taken.count() / times << std::endl;
    }

    small_p_file.close();
    large_p_file.close();
}

void test_2D_RabinKarp(const std::vector<std::string>& two_dimensional_test, int k)
{
    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;
    int times = 1000;
    ns total_time_taken = ns(0);

    int matches;

    for (size_t i = 0; i < times; ++i) {
        auto start = clock::now();
        matches = twoDimensionalRabinKarp(two_dimensional_test, k);
        auto end = clock::now();
        total_time_taken += std::chrono::duration_cast<ns>(end - start);
    }

    std::cout << "2D Rabin-Karp"<< " (matches: " << matches << "): " << total_time_taken.count() / times / 1000
              << "ms\n";
}

void test_2D_RabinKarp_step(const std::vector<std::string>& two_dimensional_test, int k)
{
    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;
    ns total_time_taken;
    int times = 1000;
    int step = 10;

    std::ofstream file_out;
    file_out.open("Rabin-Karp(2D).txt");
    std::vector<std::string> part_of_t;

    for (int size = step; size <= two_dimensional_test.size(); size+=step)
    {
        total_time_taken = ns(0);
        part_of_t.clear();

        for (int j = 0; j < size; ++j) {
            part_of_t.push_back(two_dimensional_test[j]);
        }

        for (size_t i = 0; i < times; ++i) {
            auto start = clock::now();
            twoDimensionalRabinKarp(part_of_t, k);
            auto end = clock::now();
            total_time_taken += std::chrono::duration_cast<ns>(end - start);
        }

        file_out << size << ' ' << total_time_taken.count() / times << std::endl;
    }

    file_out.close();
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

std::vector<std::string> txt_to_2d_string(std::string filename) {
    std::string tmp;
    std::vector<std::string> result;
    std::ifstream file_in;

    file_in.open(filename);
    while (getline(file_in, tmp)) {
        result.push_back(tmp);
    }

    file_in.close();

    return result;
}

#endif //ADVANCED_ALGORITHMS_HELPERS_H
