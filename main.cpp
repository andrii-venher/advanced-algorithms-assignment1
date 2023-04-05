#include <vector>
#include "PatternMatchingAlgorithms.h"
#include "Helpers.h"

int main() {
    std::string test_t = "12341235612123236123";
    std::string test_p = "123";

    std::string text = txt_to_string("text.txt");
    std::string small_pattern = txt_to_string("small_pattern.txt");
    std::string large_pattern = txt_to_string("large_pattern.txt");

    const std::string& t = text;
    const std::string& p = large_pattern;

    std::cout << "T size: " << t.size() << std::endl;
    std::cout << "P size: " << p.size() << std::endl;

    std::vector<PatternMatchingAlgorithm*> algorithms =
            {
                    new BruteForcePatternMatchingAlgorithm(),
                    new SundayPatternMatchingAlgorithm(),
                    new RabinKarpPatternMatchingAlgorithm(),
            };

    for(auto algorithm : algorithms)
    {
        test_algorithm(algorithm, t, p);
    }
}