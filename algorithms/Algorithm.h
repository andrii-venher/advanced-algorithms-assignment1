#ifndef ADVANCED_ALGORITHMS_ALGORITHM_H
#define ADVANCED_ALGORITHMS_ALGORITHM_H

#include <string>

class Algorithm {
public:
    virtual std::string get_name() = 0;
    virtual ~Algorithm() = default;
};

#endif //ADVANCED_ALGORITHMS_ALGORITHM_H
