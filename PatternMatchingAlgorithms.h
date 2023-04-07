#ifndef ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
#define ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H

#include <string>
#include <iostream>

class PatternMatchingAlgorithm {
public:
    virtual int findMatches(const std::string &t, const std::string &p) = 0;

    virtual std::string getName() = 0;
};

class BruteForcePatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int findMatches(const std::string &t, const std::string &p) override {
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

    std::string getName() override { return "Brute force"; }
};

class BinarySundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int findMatches(const std::string &t, const std::string &p) override {
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

    std::string getName() override { return "Binary Sunday"; }
};

class SundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int findMatches(const std::string &t, const std::string &p) override {
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

    std::string getName() override { return "Sunday"; }
};

class RabinKarpPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int findMatches(const std::string &t, const std::string &p) override {
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

    std::string getName() override { return "Rabin-Karp"; }
};

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
    int findMatches(const std::string &t, const std::string &p) override {
        std::string tp = p + "$" + t;
        int l = tp.length();

        int *Z = new int[l];
        build_z_array(tp, Z);

        int matches = 0;

        for (int i = 0; i < l; ++i) {
            if (Z[i] == p.length()) {
                matches++;
            }
        }
        delete[]Z;
        return matches;
    }

    std::string getName() override { return "Gusfield Z"; }
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
    int findMatches(const std::string &t, const std::string &p) override {
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

    std::string getName() override { return "KMP"; }
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
    int findMatches(const std::string &t, const std::string &p) override {
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

    std::string getName() override { return "FSM"; }
};

#endif //ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
