#include <vector>
#include "PatternMatchingAlgorithms.h"
#include "Helpers.h"

int main() {
    std::string test_t = "12341235612123236123";
    std::string test_p = "123";

    std::string text = txt_to_string("text.txt");
    std::string small_pattern = txt_to_string("small_pattern.txt");
    std::string large_pattern = txt_to_string("large_pattern.txt");

    std::string first_case_text = txt_to_string("first_case_text.txt");
    std::string first_case_pattern = txt_to_string("first_case_pattern.txt");
    std::string second_case_text = txt_to_string("second_case_text.txt");
    std::string second_case_pattern = txt_to_string("second_case_pattern.txt");
    std::string third_case_text = txt_to_string("third_case_text.txt");
    std::string third_case_pattern = txt_to_string("third_case_pattern.txt");

    const std::string& t = third_case_text;
    const std::string& p = third_case_pattern;

    std::cout << "T size: " << t.size() << std::endl;
    std::cout << "P size: " << p.size() << std::endl;

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

    for(auto algorithm : algorithms)
    {
        test_algorithm(algorithm, t, p);
    }
}