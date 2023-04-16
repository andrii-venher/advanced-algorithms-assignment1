#include <iostream>
#include <chrono>
#include <fstream>
#include <utility>
#include "TestRunner.h"
#include "algorithms/TwoDimensionalRabinKarpPatternMatchingAlgorithm.h"

std::string TestRunner::txt_to_string(const std::string &filename) {
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

void TestRunner::test_algorithm(PatternMatchingAlgorithm *algorithm, const std::string &t, const std::string &p, int times) {
    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;
    ns total_time_taken = ns(0);

    int matches;

    for (size_t i = 0; i < times; ++i) {
        auto start = clock::now();
        matches = algorithm->find_matches(t, p);
        auto end = clock::now();
        total_time_taken += std::chrono::duration_cast<ns>(end - start);
    }

    std::cout << algorithm->get_name() << " (matches: " << matches << "): "
              << total_time_taken.count() / times / 1000
              << "ms.\n";
}

void TestRunner::test_wildcard_algorithm(WildcardPatternMatchingAlgorithm *algorithm, const std::string &t,
                                         const std::string &p) {
    bool match;

    try {
        match = algorithm->find_match(t, p);
    } catch (const std::logic_error &ex) {
        std::cout << algorithm->get_name() << " has thrown an exception: " << ex.what() << std::endl;
        return;
    }

    std::cout << algorithm->get_name() << " (match is " << (match ? "found" : "not found") << ")." << std::endl;
}

bool TestRunner::test_wildcard_algorithm_using_test_case(WildcardPatternMatchingAlgorithm *algorithm,
                                                         const TestCase &test_case) {
    bool match;

    std::cout << "t:\t" << test_case.t << std::endl;
    std::cout << "p:\t" << test_case.p << std::endl;
    std::cout << "?:\t" << (test_case.expected ? "found" : "not found") << std::endl;

    try {
        match = algorithm->find_match(test_case.t, test_case.p);
    } catch (const std::logic_error &ex) {
        std::cout << algorithm->get_name() << " has thrown an exception: " << ex.what() << std::endl;
        return false;
    }

    bool assert = match == test_case.expected;

    std::cout << algorithm->get_name() << " (match is " << (match ? "found" : "not found") << ") -> "
              << (assert ? "pass" : "fail") << "." << std::endl;

    return assert;
}

void TestRunner::load_wildcard_test_cases() {
    std::string t;
    std::ifstream file_in;

    file_in.open("wildcard_test_cases.txt");

    while (getline(file_in, t)) {
        std::string p;
        std::string expected_as_string;
        getline(file_in, p);
        getline(file_in, expected_as_string);
        bool expected = expected_as_string == "1";
        test_cases.emplace_back(TestCase(t, p, expected));
        // Skip separator line
        getline(file_in, p);
    }
    file_in.close();
}

void TestRunner::load_static_assets() {
    text = txt_to_string("text.txt");
    second_case_text = txt_to_string("second_case_text.txt");
    small_pattern = txt_to_string("small_pattern.txt");
    large_pattern = txt_to_string("large_pattern.txt");
    second_case_pattern = txt_to_string("second_case_pattern.txt");
    two_dimensional_test = txt_to_2d_string("two_dimensional_text.txt");
    load_wildcard_test_cases();
}

TestRunner::TestRunner() {
    load_static_assets();
}

void TestRunner::test_algorithms(const std::vector<std::unique_ptr<PatternMatchingAlgorithm>> &algorithms, const std::string &t,
                                 const std::string &p, int times) {
    std::cout << "************* " << "Pattern matching algorithms" << " *************" << std::endl << std::endl;
    for (const auto &algorithm: algorithms) {
        test_algorithm(algorithm.get(), t, p, times);
    }
    std::cout << std::endl;
}

void TestRunner::test_wildcards_algorithms_using_test_cases(
        const std::vector<std::unique_ptr<WildcardPatternMatchingAlgorithm>> &algorithms) {
    std::cout << "************* " << "Wildcard pattern matching algorithms" << " *************" << std::endl;
    for (const auto &algorithm: algorithms) {
        std::cout << std::endl << "------------- " << algorithm->get_name() << " -------------" << std::endl;
        int passed = 0;
        for (const auto &test_case: test_cases) {
            bool pass = test_wildcard_algorithm_using_test_case(algorithm.get(), test_case);
            if (pass) {
                passed++;
            }
        }
        std::cout << std::endl << "Passed: " << passed << " out of " << test_cases.size() << std::endl;
    }
    std::cout << std::endl;
}

void TestRunner::test_2d_rabin_karp(int k) {
    std::cout << "************* " << TwoDimensionalRabinKarpPatternMatchingAlgorithm::get_name() << " *************" << std::endl << std::endl;
    std::cout << "N of rows: " << two_dimensional_test.size() << std::endl;
    std::cout << "K: " << k << std::endl;

    using clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;
    int times = 1000;
    ns total_time_taken = ns(0);

    int matches;

    for (size_t i = 0; i < times; ++i) {
        auto start = clock::now();
        matches = TwoDimensionalRabinKarpPatternMatchingAlgorithm::find_matches(two_dimensional_test, k);
        auto end = clock::now();
        total_time_taken += std::chrono::duration_cast<ns>(end - start);
    }

    std::cout << TwoDimensionalRabinKarpPatternMatchingAlgorithm::get_name() << " (matches: " << matches << "): " << total_time_taken.count() / times / 1000
              << "ms.\n";

    std::cout << std::endl;
}

std::vector<std::string> TestRunner::txt_to_2d_string(std::string filename) {
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