#include "PatternMatchingAlgorithm.h"

int BruteForcePatternMatchingAlgorithm::find_matches(const std::string &t, const std::string &p) {
    size_t t_size = t.size();
    size_t p_size = p.size();
    bool found;

    int matches = 0;

    for (size_t i = 0; i <= t_size - p_size; ++i) {
        found = true;

        for (size_t j = 0; j < p_size; ++j) {
            if (t[i + j] != p[j]) {
                found = false;
                break;
            }
        }

        if (found) {
            matches++;
        }
    }

    return matches;
}

std::string BruteForcePatternMatchingAlgorithm::get_name() { return "Brute force"; }