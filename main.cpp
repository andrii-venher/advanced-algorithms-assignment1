#include <vector>
#include "PatternMatchingAlgorithms.h"
#include "Helpers.h"

int main() {
    std::string text = txt_to_string("text.txt");
    std::string small_pattern = txt_to_string("small_pattern.txt");
    std::string large_pattern = txt_to_string("large_pattern.txt");

    std::string first_case_text = txt_to_string("first_case_text.txt");
    std::string first_case_pattern = txt_to_string("first_case_pattern.txt");
    std::string second_case_text = txt_to_string("second_case_text.txt");
    std::string second_case_pattern = txt_to_string("second_case_pattern.txt");
    std::string third_case_text = txt_to_string("third_case_text.txt");
    std::string third_case_pattern = txt_to_string("third_case_pattern.txt");

    const std::string& t = text;
    const std::string& p = small_pattern;
    const std::string& large_p = large_pattern;

    std::vector<PatternMatchingAlgorithm*> algorithms =
            {
                    new BruteForcePatternMatchingAlgorithm(),
                    new BinarySundayPatternMatchingAlgorithm(),
                    new SundayPatternMatchingAlgorithm(),
                    new RabinKarpPatternMatchingAlgorithm(),
                    new GusfieldZPatternMatchingAlgorithm(),
                    new KMPPatternMatchingAlgorithm(),
                    new FSMPatternMatchingAlgorithm()
            };

    std::cout << "T size: " << t.size() << std::endl;
    std::cout << "P size: " << p.size() << std::endl;

    for(auto algorithm : algorithms)
    {
        test_algorithm(algorithm, t, p);
        test_algorithm_step(algorithm, text, p, large_p);
    }

    int k = 4;
    std::vector<std::string> two_dimensional_test = txt_to_2d_string("two_dimensional_text.txt");

    std::cout << std::endl << "N of rows: " << two_dimensional_test.size() << std::endl;
    std::cout << "K: " << k << std::endl;

    test2DRabinKarp(two_dimensional_test, k);
}