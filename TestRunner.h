#ifndef ADVANCED_ALGORITHMS_TESTRUNNER_H
#define ADVANCED_ALGORITHMS_TESTRUNNER_H

#include <vector>
#include <memory>
#include "algorithms/PatternMatchingAlgorithm.h"
#include "algorithms/WildcardPatternMatchingAlgorithm.h"

class TestRunner {
    std::vector<std::string> two_dimensional_test;

    struct TestCase {
        std::string t;
        std::string p;
        bool expected;

        TestCase(std::string t, std::string p, bool expected) : t(std::move(t)), p(std::move(p)), expected(expected) {}
    };

    std::string txt_to_string(const std::string &filename);

    std::vector<std::string> txt_to_2d_string(std::string filename);

    static void test_algorithm(PatternMatchingAlgorithm *algorithm, const std::string &t, const std::string &p, int times);

    static void test_wildcard_algorithm(WildcardPatternMatchingAlgorithm *algorithm, const std::string &t, const std::string &p);

    static bool test_wildcard_algorithm_using_test_case(WildcardPatternMatchingAlgorithm *algorithm, const TestCase &test_case);

    void load_wildcard_test_cases();

    void load_static_assets();

public:
    std::vector<TestCase> test_cases;
    std::string text;
    std::string second_case_text;
    std::string small_pattern;
    std::string large_pattern;
    std::string second_case_pattern;

    TestRunner();

    void test_algorithms(const std::vector<std::unique_ptr<PatternMatchingAlgorithm>> &algorithms, const std::string &t,
                         const std::string &p, int times);

    void test_wildcards_algorithms_using_test_cases(const std::vector<std::unique_ptr<WildcardPatternMatchingAlgorithm>> &algorithms);

    void test_2d_rabin_karp(int k);
};


#endif //ADVANCED_ALGORITHMS_TESTRUNNER_H
