#include <sstream>
#include "WildcardPatternMatchingAlgorithm.h"

Match WildcardBruteForcePatternMatchingAlgorithm::find_match_without_star(const std::string &t, const std::string &p) {
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
        } else {
            consecutive_matches++;
        }

        text_cursor++;
        pattern_cursor++;
    }

    bool found = pattern_cursor == p_size;
    if (found) {
        return {true, text_cursor - consecutive_matches, text_cursor};
    } else {
        return {false, -1, -1};
    }
}

std::string WildcardBruteForcePatternMatchingAlgorithm::get_name() {
    return "Wildcard brute force";
}