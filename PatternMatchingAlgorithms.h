#ifndef ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
#define ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

class Algorithm {
public:
    virtual std::string get_name() = 0;
};

class PatternMatchingAlgorithm : public Algorithm {
public:
    virtual int find_matches(const std::string &t, const std::string &p) = 0;
};

class WildcardPatternMatchingAlgorithm : public Algorithm {
public:
    virtual bool find_match(const std::string &t, const std::string &p) = 0;
};

class BruteForcePatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override {
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

    std::string get_name() override { return "Brute force"; }
};

class WildcardBruteForcePatternMatchingAlgorithm : public WildcardPatternMatchingAlgorithm {
private:
    struct Match {
        bool found;
        int start_index;
        int end_index;
        Match(bool found, int start_index, int end_index) : found(found), start_index(start_index), end_index(end_index) {}
    };

    Match find_match_without_star(const std::string &t, const std::string &p) {
        size_t t_size = t.size();
        size_t p_size = p.size();

        int text_cursor = 0;
        int pattern_cursor = 0;

        int consecutive_matches = 0;

        while (pattern_cursor < p_size) {
            if (text_cursor >= t_size) {
                break;
            }

            char current_text_char = t[text_cursor];
            char current_pattern_char = p[pattern_cursor];

            // Escaped backslash or question mark, match exactly
            if (current_pattern_char == '\\') {
                char next_after_current_pattern_char = p[pattern_cursor + 1];
                if (current_text_char != next_after_current_pattern_char) {
                    pattern_cursor = 0;
                    text_cursor -= consecutive_matches - 1;
                    consecutive_matches = 0;
                    continue;
                } else {
                    consecutive_matches++;
                    pattern_cursor++;
                }
            }
            // Question mark wildcard, match any character
            else if (current_pattern_char == '?') {
                consecutive_matches++;
             }
            // Any other character, match exactly
            else if (current_text_char != current_pattern_char) {
                pattern_cursor = 0;
                text_cursor -= consecutive_matches - 1;
                consecutive_matches = 0;
                continue;
            }
            else {
                consecutive_matches++;
            }

            text_cursor++;
            pattern_cursor++;
        }

        bool found = pattern_cursor == p_size;
        if (found) {
            return {true, text_cursor - consecutive_matches, text_cursor};
        }
        else {
            return {false, -1, -1};
        }
    }

public:
    bool find_match(const std::string &t, const std::string &pattern) override {
        std::string p = pattern;

        size_t t_size = t.size();
        size_t p_size = p.size();

        // Check if pattern has correct format, i.e. after backslash is not a wildcard and not another backslash
        if (p_size == 1 && p[0] == '\\') {
            throw std::logic_error("Pattern is incorrect. Invalid sequence at index 0: \\");
        }
        for (int i = 0; i < p_size; ++i) {
            if (p[i] == '\\') {
                if (i < p_size - 1 && p[i + 1] != '*' && p[i + 1] != '?' && p[i + 1] != '\\') {
                    throw std::logic_error("Pattern is incorrect. Invalid sequence at index " + std::to_string(i) + ": "
                                           + std::string(1, p[i]) + std::string(1, p[i + 1]));
                }
                if (i == p_size - 1 && p_size >= 1 && p[i - 1] != '\\') {
                    throw std::logic_error(
                            "Pattern is incorrect. Invalid sequence at index " + std::to_string(i) + ": \\");
                }
            }
        }

        // Preprocess pattern to merge duplicate stars which are next to each other
        std::stringstream new_p;
        for (int i = 0; i < p_size; ++i) {
            if (p[i] == '*') {
                int j = i + 1;
                while (j < p_size && p[j] == '*')
                {
                    j++;
                }
                i = j - 1;
            }
            new_p << p[i];
        }
        p = new_p.str();
        p_size = p.size();

        int text_cursor = 0;
        int pattern_cursor = 0;

        int index_of_first_star = -1;
        for (int i = 0; i < p_size; ++i) {
            if (p[i] == '*' && (i == 0 || (i > 0 && p[i - 1] != '\\'))) {
                index_of_first_star = i;
                break;
            }
        }
        if (index_of_first_star >= 0) {
            Match initial_match = find_match_without_star(t, p.substr(0, index_of_first_star));
            if(!initial_match.found)
            {
                return false;
            }
            text_cursor = initial_match.end_index;
            pattern_cursor = index_of_first_star;
        }

        while (pattern_cursor < p_size) {
            // End of the text reached, pattern not found yet
            if (text_cursor >= t_size) {
                break;
            }

            int index_of_next_star = -1;
            for (int i = pattern_cursor + 1; i < p_size; ++i) {
                if (p[i] == '*' && p[i - 1] != '\\') {
                    index_of_next_star = i;
                    break;
                }
            }
            // This is the last star in the pattern
            if (index_of_next_star == -1) {
                // No more pattern characters after it, so trivial
                if (pattern_cursor == p_size - 1) {
                    return true;
                }
                    // Check if there is a match in the rest of the pattern
                else {
                    return find_match_without_star(t.substr(text_cursor), p.substr(pattern_cursor + 1)).found;
                }
            }
                // There is another star in the pattern
            else {
                std::string text_to_match = t.substr(text_cursor);
                std::string pattern_to_match = p.substr(pattern_cursor + 1, index_of_next_star - pattern_cursor - 1);
                Match match_between = find_match_without_star(text_to_match, pattern_to_match);
                if (!match_between.found) {
                    return false;
                }
                pattern_cursor = index_of_next_star;
                text_cursor += match_between.end_index;
            }

            // Last pattern star reached, and it is at the last index, so trivial
            if (pattern_cursor == p_size - 1) {
                return true;
            }
        }

        return false;
    }

    std::string get_name() override {
        return "Wildcard brute force";
    }
};

class BinarySundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override {
        size_t t_size = t.size();
        size_t p_size = p.size();

        std::vector<int> positions(256, 0);

        for (int i = 0; i < p_size; ++i) {
            positions[p[i]] = 1;
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
            }

            if (t_index + p_size < t_size && positions[t[t_index + p_size]] == 0) {
                t_index += p_size + 1;
            } else {
                ++t_index;
            }
        }
        return matches;
    }

    std::string get_name() override { return "Binary Sunday"; }
};

class SundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override {
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

    std::string get_name() override { return "Sunday"; }
};

class RabinKarpPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override {
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

    std::string get_name() override { return "Rabin-Karp"; }
};

int twoDimensionalRabinKarp(const std::vector<std::string> &list, int k) {
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

class GusfieldZPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
private:
    static void build_z_array(const std::string &tp, int Z[]) {
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

public:
    int find_matches(const std::string &t, const std::string &p) override {
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

    std::string get_name() override { return "Gusfield Z"; }
};

class KMPPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
private:
    static void build_lps_array(const std::string &p, int lps[]) {
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

public:
    int find_matches(const std::string &t, const std::string &p) override {
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

    std::string get_name() override { return "KMP"; }
};

class FSMPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
private:
    int getNextState(const std::string &p, size_t p_size, int state, int x) {
        if (state < p_size && x == p[state])
            return state + 1;

        int ns, i;

        for (ns = state; ns > 0; ns--) {
            if (p[ns - 1] == x) {
                for (i = 0; i < ns - 1; i++)
                    if (p[i] != p[state - ns + 1 + i])
                        break;
                if (i == ns - 1)
                    return ns;
            }
        }

        return 0;
    }

    void computeTF(const std::string &p, size_t p_size, int **tf) {
        int state, x;
        for (state = 0; state <= p_size; ++state)
            for (x = 0; x < 256; ++x)
                tf[state][x] = getNextState(p, p_size, state, x);
    }

public:
    int find_matches(const std::string &t, const std::string &p) override {
        int matches = 0;
        size_t p_size = p.length();
        size_t t_size = t.length();

        int **tf = new int *[p_size + 1];

        for (int i = 0; i < p_size + 1; ++i) {
            tf[i] = new int[256];
        }

        computeTF(p, p_size, tf);

        int i, state = 0;
        for (i = 0; i < t_size; i++) {
            state = tf[state][t[i]];
            if (state == p_size)
                ++matches;
        }

        for (int j = 0; j < p_size + 1; ++j) {
            delete[] tf[j];
        }

        delete[]tf;

        return matches;
    }

    std::string get_name() override { return "FSM"; }
};

#endif //ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
