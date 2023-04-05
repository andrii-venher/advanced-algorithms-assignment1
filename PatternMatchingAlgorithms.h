#ifndef ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
#define ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H

#include <string>

class PatternMatchingAlgorithm {
public:
    virtual void findMatches(std::string t, std::string p) = 0;

    virtual std::string getName() = 0;
};

class BruteForcePatternMatchingAlgorithm : public PatternMatchingAlgorithm {
    void findMatches(std::string t, std::string p) override {
        size_t t_size = t.size();
        size_t p_size = p.size();
        bool found;

        for (size_t i = 0; i <= t_size - p_size; ++i) {
            found = true;

            for (size_t j = 0; j < p_size; ++j) {
                if (t[i + j] != p[j]) {
                    found = false;
                    break;
                }
            }

            if (found) {
                //cout << "Pattern found!\n";
            }
        }
    }

    std::string getName() override { return "Brute force"; }
};

class SundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
    void findMatches(std::string t, std::string p) override {
        size_t t_size = t.size();
        size_t p_size = p.size();

        std::vector<int> positions(256, -1);

        for (int i = 0; i < p_size; ++i) {
            positions[p[i]] = i;
        }

        size_t t_index = 0;
        while (t_index <= t_size - p_size) {
            size_t p_index = p_size - 1;

            while (p_index >= 0 && p[p_index] == t[t_index + p_index]) {
                --p_index;
            }

            if (p_index < 0) {
                //cout << "Pattern found!" << endl;

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
    }

    std::string getName() override { return "Sunday"; }
};

class RabinKarpPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
    void findMatches(std::string t, std::string p) override {
        int t_size = t.size();
        int p_size = p.size();
        int p_hash = 0;
        int t_hash = 0;
        int coef = 127;
        int max_coef = 1;
        int mod = INT_MAX / 2 + 1;
        bool found;

        for (int i = 0; i < p_size - 1; ++i) {
            max_coef = (max_coef * coef) % mod;
        }

        for (int i = 0; i < p_size; ++i) {
            p_hash = (p_hash * coef + p[i]) % mod;
            t_hash = (t_hash * coef + t[i]) % mod;
        }

        for (int i = 0; i <= t_size - p_size; ++i) {
            if (p_hash == t_hash) {
                found = true;
                for (int j = 0; j < p_size; ++j) {
                    if (t[i + j] != p[j]) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    //cout << "Pattern found!\n";
                }
            }

            if (i < t_size - p_size) {
                t_hash = (coef * (t_hash - t[i] * max_coef) + t[i + p_size]) % mod;

                if (t_hash < 0) {
                    t_hash += mod;
                }
            }
        }
    }

    std::string getName() override { return "Rabin-Karp"; }
};

#endif //ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
