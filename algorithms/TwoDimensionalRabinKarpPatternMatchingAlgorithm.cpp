#include "TwoDimensionalRabinKarpPatternMatchingAlgorithm.h"

int TwoDimensionalRabinKarpPatternMatchingAlgorithm::find_matches(const std::vector<std::string> &list, int k) {
    unsigned int coef = 256;
    unsigned int max_coef = 1;
    unsigned int p_hash = 0;
    unsigned int t_hash = 0;
    int matches = 0;
    size_t row_length = list[0].size();

    for (int i = 0; i < k - 1; ++i) {
        max_coef = max_coef * coef;
    }

    std::vector<unsigned int> current_row_hashes(row_length, 0);

    for (int i = 0; i < row_length; ++i) {
        unsigned int column_hash = 0;

        for (int j = 0; j < k; ++j) {
            column_hash = column_hash * coef + list[j][i];
        }

        current_row_hashes[i] = column_hash;

        if (i < k) {
            t_hash = t_hash * coef + column_hash;
        } else {
            t_hash = coef * (t_hash - current_row_hashes[i - k] * max_coef) + column_hash;
            if (t_hash == p_hash) {
                ++matches;
                for (int t = 0; t < k; ++t) {
                    for (int l = 0; l < k; ++l) {
                        if (list[t][l] != list[t][l + i + 1 - k]) {
                            --matches;
                            break;
                        }
                    }
                }
            }
        }

        if (i == k - 1) {
            p_hash = t_hash;
        }
    }

    for (int i = 1; i <= list.size() - k; ++i) {
        for (int j = 0; j < row_length; ++j) {
            current_row_hashes[j] = coef * (current_row_hashes[j] - list[i - 1][j] * max_coef) + list[i + k - 1][j];
        }

        t_hash = 0;

        for (int j = 0; j < row_length; ++j) {
            if (j < k) {
                t_hash = t_hash * coef + current_row_hashes[j];
            } else {
                t_hash = coef * (t_hash - current_row_hashes[j - k] * max_coef) + current_row_hashes[j];
            }

            if (t_hash == p_hash) {
                ++matches;
                for (int t = 0; t < k; ++t) {
                    for (int l = 0; l < k; ++l) {
                        if (list[t][l] != list[t + i][l + j + 1 - k]) {
                            --matches;
                            break;
                        }
                    }
                }
            }
        }
    }

    return matches;
}

std::string TwoDimensionalRabinKarpPatternMatchingAlgorithm::get_name() { return "2D Rabin-Karp"; }