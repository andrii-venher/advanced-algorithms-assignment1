#ifndef ADVANCED_ALGORITHMS_WILDCARDPATTERNMATCHINGALGORITHM_H
#define ADVANCED_ALGORITHMS_WILDCARDPATTERNMATCHINGALGORITHM_H

#include "Algorithm.h"

struct Match {
    bool found;
    int start_index;
    int end_index;

    Match(bool found, int start_index, int end_index) : found(found), start_index(start_index), end_index(end_index) {}
};

class WildcardPatternMatchingAlgorithm : public Algorithm {
    int find_next_star_index(const std::string &p, int start_index);

protected:
    virtual Match find_match_without_star(const std::string &t, const std::string &p) = 0;

public:
    bool find_match(const std::string &t, const std::string &pattern);

    ~WildcardPatternMatchingAlgorithm() override = default;
};

class WildcardBruteForcePatternMatchingAlgorithm : public WildcardPatternMatchingAlgorithm {
protected:
    Match find_match_without_star(const std::string &t, const std::string &p) override;

public:

    std::string get_name() override;
};

class WildcardSundayPatternMatchingAlgorithm : public WildcardPatternMatchingAlgorithm {
protected:
    Match find_match_without_star(const std::string &t, const std::string &p) override;

public:

    std::string get_name() override;
};

#endif //ADVANCED_ALGORITHMS_WILDCARDPATTERNMATCHINGALGORITHM_H
