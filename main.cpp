#include <vector>
#include "PatternMatchingAlgorithms.h"
#include "TestRunner.h"

int main() {
    TestRunner test_runner;

//    std::vector<PatternMatchingAlgorithm *> algorithms = {
//            new BruteForcePatternMatchingAlgorithm(),
//            new BinarySundayPatternMatchingAlgorithm(),
//            new SundayPatternMatchingAlgorithm(),
//            new RabinKarpPatternMatchingAlgorithm(),
//            new GusfieldZPatternMatchingAlgorithm(),
//            new KMPPatternMatchingAlgorithm(),
//            new FSMPatternMatchingAlgorithm(),
//    };
//
//    test_runner.test_algorithms(algorithms, test_runner.text, test_runner.large_pattern);

    std::vector<WildcardPatternMatchingAlgorithm *> wildcard_algorithms =
            {
                    new WildcardBruteForcePatternMatchingAlgorithm()
            };

    test_runner.test_wildcards_algorithms_using_test_cases(wildcard_algorithms);
}