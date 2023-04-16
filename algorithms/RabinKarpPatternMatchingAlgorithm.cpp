#include "PatternMatchingAlgorithm.h"

int RabinKarpPatternMatchingAlgorithm::find_matches(const std::string &t, const std::string &p) {
    size_t t_size = t.size();
    size_t p_size = p.size();
    unsigned int p_hash = 0;
    unsigned int t_hash = 0;
    unsigned int coef = 256;
    unsigned int max_coef = 1;
    int i, j = 0;
    int matches = 0;

    for (i = 0; i < p_size - 1; ++i) {
        max_coef = max_coef * coef;
    }

    for (i = 0; i < p_size; ++i) {
        p_hash = p_hash * coef + p[i];
        t_hash = t_hash * coef + t[i];
    }

    for (i = 0; i <= t_size - p_size; ++i) {
        if (p_hash == t_hash) {
            for (j = 0; j < p_size; ++j) {
                if (t[i + j] != p[j]) {
                    break;
                }
            }

            if (j == p_size) {
                matches++;
            }
        }

        if (i < t_size - p_size) {
            t_hash = coef * (t_hash - t[i] * max_coef) + t[i + p_size];
        }
    }
    return matches;
}

std::string RabinKarpPatternMatchingAlgorithm::get_name() { return "Rabin-Karp"; }