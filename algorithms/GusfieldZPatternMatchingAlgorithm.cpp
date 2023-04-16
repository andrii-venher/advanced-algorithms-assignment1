#include "PatternMatchingAlgorithm.h"

void GusfieldZPatternMatchingAlgorithm::build_z_array(const std::string &tp, int Z[]) {
    int length = tp.length();
    int left, right, k;

    left = right = 0;
    for (int i = 1; i < length; ++i) {
        if (i > right) {
            left = right = i;

            while (right < length && tp[right - left] == tp[right]) {
                right++;
            }
            Z[i] = right - left;
            right--;
        } else {
            k = i - left;

            if (Z[k] < right - i + 1) {
                Z[i] = Z[k];
            } else {
                left = i;
                while (right < length && tp[right - left] == tp[right]) {
                    right++;
                }
                Z[i] = right - left;
                right--;
            }
        }
    }
}

int GusfieldZPatternMatchingAlgorithm::find_matches(const std::string &t, const std::string &p) {
    std::string tp = p + "$" + t;
    const int l = tp.length();

    int Z[l];
    build_z_array(tp, Z);

    int matches = 0;

    for (int i = 0; i < l; ++i) {
        if (Z[i] == p.length()) {
            matches++;
        }
    }

    return matches;
}

std::string GusfieldZPatternMatchingAlgorithm::get_name() { return "Gusfield Z"; }