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

    int k = 4;
    std::vector<std::string> two_dimensional_test = txt_to_2d_string("two_dimensional_text.txt");
    std::cout << std::endl << "N of rows: " << two_dimensional_test.size() << std::endl;
    std::cout << "K: " << k << std::endl;

    test_2D_RabinKarp(two_dimensional_test, k);
}