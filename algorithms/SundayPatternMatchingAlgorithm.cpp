#include <vector>
#include "PatternMatchingAlgorithm.h"

int SundayPatternMatchingAlgorithm::find_matches(const std::string &t, const std::string &p) {
    size_t t_size = t.size();
    size_t p_size = p.size();

    std::vector<int> positions(256, -1);

    for (int i = 0; i < p_size; ++i) {
        positions[p[i]] = i;
    }
    int matches = 0;

    size_t t_index = 0;
    while (t_index <= t_size - p_size) {
        int p_index = p_size - 1;

        while (p_index >= 0 && p[p_index] == t[t_index + p_index]) {
            --p_index;
        }

        if (p_index < 0) {
            matches++;

            if (t_index + p_size < t_size) {
                t_index += p_size - positions[t[t_index + p_size]];
            } else {
                ++t_index;
            }
        } else {
            int shift = p_index - positions[t[t_index + p_index]];

            if (shift > 0) {
                t_index += shift;
            } else {
                ++t_index;
            }
        }
    }
    return matches;
}

std::string SundayPatternMatchingAlgorithm::get_name() { return "Sunday"; }