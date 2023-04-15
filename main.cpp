#include <vector>
#include "TestRunner.h"

int main() {
    TestRunner test_runner;

//    std::vector<PatternMatchingAlgorithm *> algorithms = {
//            new SundayPatternMatchingAlgorithm(),
//    };
//
//    test_runner.test_algorithms(algorithms, test_runner.text, test_runner.small_pattern);

    std::vector<WildcardPatternMatchingAlgorithm *> wildcard_algorithms =
            {
                    new WildcardBruteForcePatternMatchingAlgorithm(),
                    new WildcardSundayPatternMatchingAlgorithm(),
            };

    test_runner.test_wildcards_algorithms_using_test_cases(wildcard_algorithms);

//    test_runner.test_2d_rabin_karp(4);
}