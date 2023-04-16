#include "PatternMatchingAlgorithm.h"

int FSMPatternMatchingAlgorithm::getNextState(const std::string &p, size_t p_size, int state, int x) {
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

void FSMPatternMatchingAlgorithm::computeTF(const std::string &p, size_t p_size, int **tf) {
    int state, x;
    for (state = 0; state <= p_size; ++state)
        for (x = 0; x < 256; ++x)
            tf[state][x] = getNextState(p, p_size, state, x);
}

int FSMPatternMatchingAlgorithm::find_matches(const std::string &t, const std::string &p) {
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

std::string FSMPatternMatchingAlgorithm::get_name() { return "FSM"; }