#ifndef ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
#define ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H

#include "Algorithm.h"
#include <vector>

class PatternMatchingAlgorithm : public Algorithm {
public:
    virtual int find_matches(const std::string &t, const std::string &p) = 0;
};

class BruteForcePatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};

class SundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};

class BinarySundayPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};

class RabinKarpPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};

class GusfieldZPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
private:
    static void build_z_array(const std::string &tp, int Z[]);

public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};

class KMPPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
private:
    static void build_lps_array(const std::string &p, int lps[]);

public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};

class FSMPatternMatchingAlgorithm : public PatternMatchingAlgorithm {
private:
    int getNextState(const std::string &p, size_t p_size, int state, int x);

    void computeTF(const std::string &p, size_t p_size, int **tf);

public:
    int find_matches(const std::string &t, const std::string &p) override;

    std::string get_name() override;
};



#endif //ADVANCED_ALGORITHMS_PATTERNMATCHINGALGORITHM_H
