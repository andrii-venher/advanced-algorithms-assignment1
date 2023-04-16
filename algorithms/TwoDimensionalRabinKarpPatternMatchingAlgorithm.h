#ifndef ADVANCED_ALGORITHMS_TWODIMENSIONALRABINKARPPATTERNMATCHINGALGORITHM_H
#define ADVANCED_ALGORITHMS_TWODIMENSIONALRABINKARPPATTERNMATCHINGALGORITHM_H

#include <string>
#include <vector>

class TwoDimensionalRabinKarpPatternMatchingAlgorithm {
public:
    static int find_matches(const std::vector<std::string> &list, int k);

    static std::string get_name();
};

#endif //ADVANCED_ALGORITHMS_TWODIMENSIONALRABINKARPPATTERNMATCHINGALGORITHM_H
