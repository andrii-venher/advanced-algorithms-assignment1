#include <vector>
#include "PatternMatchingAlgorithms.h"
#include "Helpers.h"

int main() {
    std::string test_t = "12341235612123236123";
    std::string test_p = "123";

    std::string text = txt_to_string("text.txt");
    std::string second_case_text = txt_to_string("second_case_text.txt");
    std::string small_pattern = txt_to_string("small_pattern.txt");
    std::string large_pattern = txt_to_string("large_pattern.txt");
    std::string second_case_pattern = txt_to_string("second_case_pattern.txt");

    const std::string& t = text;
    const std::string& p = small_pattern;

    std::cout << "T size: " << t.size() << std::endl;
    std::cout << "P size: " << p.size() << std::endl;

    std::vector<PatternMatchingAlgorithm*> algorithms =
            {
                    new BruteForcePatternMatchingAlgorithm(),
                    new SundayPatternMatchingAlgorithm(),
                    new RabinKarpPatternMatchingAlgorithm(),
                    new GusfieldZPatternMatchingAlgorithm(),
                    new KMPPatternMatchingAlgorithm(),
                    new FSMPatternMatchingAlgorithm()
            };

    for(auto algorithm : algorithms)
    {
        test_algorithm(algorithm, t, p);
    }
}