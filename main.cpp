#include <iostream>
#include <fstream>
#include <vector>
#include "PatternMatchingAlgorithms.h"
#include "Helpers.h"

using namespace std;

int main() {
    string test_t = "12341235612123236123";
    string test_p = "123";

    string text = txt_to_string("text.txt");
    string small_pattern = txt_to_string("small_pattern.txt");
    string large_pattern = txt_to_string("large_pattern.txt");

    vector<PatternMatchingAlgorithm*> algorithms =
            {
                    new BruteForcePatternMatchingAlgorithm(),
                    new SundayPatternMatchingAlgorithm(),
                    new RabinKarpPatternMatchingAlgorithm(),
            };

    for(auto algorithm : algorithms)
    {
        test_algorithm(algorithm, text, large_pattern);
    }
}