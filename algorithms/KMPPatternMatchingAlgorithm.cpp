#include "PatternMatchingAlgorithm.h"

void KMPPatternMatchingAlgorithm::build_lps_array(const std::string &p, int lps[]) {
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < p.length()) {
        if (p[i] == p[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len == 0) {
                lps[i] = 0;
                i++;
            } else {
                len = lps[len - 1];
            }
        }
    }
}

int KMPPatternMatchingAlgorithm::find_matches(const std::string &t, const std::string &p) {
    int n = t.length();
    int m = p.length();

    int *lps = new int[m];

    build_lps_array(p, lps);

    int matches = 0;

    int i = 0, j = 0;
    while ((n - i) >= (m - j)) {
        if (p[j] == t[i]) {
            j++;
            i++;
        }
        if (j == m) {
            matches++;
            j = lps[j - 1];
        } else if (i < n && p[j] != t[i]) {
            if (j == 0) {
                i = i + 1;
            } else {
                j = lps[j - 1];
            }

        }
    }
    delete[]lps;
    return matches;
}

std::string KMPPatternMatchingAlgorithm::get_name() { return "KMP"; }