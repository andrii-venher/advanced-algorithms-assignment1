#include <vector>
#include "TestRunner.h"

void test_algorithms(TestRunner &test_runner) {
    std::vector<std::unique_ptr<PatternMatchingAlgorithm>> algorithms;

    algorithms.emplace_back(new BruteForcePatternMatchingAlgorithm());
    algorithms.emplace_back(new SundayPatternMatchingAlgorithm());
    algorithms.emplace_back(new BinarySundayPatternMatchingAlgorithm());
    algorithms.emplace_back(new KMPPatternMatchingAlgorithm());
    algorithms.emplace_back(new FSMPatternMatchingAlgorithm());
    algorithms.emplace_back(new RabinKarpPatternMatchingAlgorithm());
    algorithms.emplace_back(new GusfieldZPatternMatchingAlgorithm());

    int times = 10;

    test_runner.test_algorithms(algorithms, test_runner.text, test_runner.small_pattern, times);
}

void test_wildcard_algorithms(TestRunner &test_runner) {
    std::vector<std::unique_ptr<WildcardPatternMatchingAlgorithm>> wildcard_algorithms;

    wildcard_algorithms.emplace_back(new WildcardBruteForcePatternMatchingAlgorithm());
    wildcard_algorithms.emplace_back(new WildcardSundayPatternMatchingAlgorithm());

    test_runner.test_wildcards_algorithms_using_test_cases(wildcard_algorithms);
}

void test_2d_rabin_karp(TestRunner &test_runner) {
    test_runner.test_2d_rabin_karp(4);
}

int main() {
    TestRunner test_runner;

    test_algorithms(test_runner);

    test_wildcard_algorithms(test_runner);

    test_2d_rabin_karp(test_runner);
}