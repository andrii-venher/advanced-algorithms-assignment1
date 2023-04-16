#include <vector>
#include <sstream>
#include "WildcardPatternMatchingAlgorithm.h"

Match WildcardSundayPatternMatchingAlgorithm::find_match_without_star(const std::string &t, const std::string &p) {
    int t_size = t.size();
    int p_size = p.size();

    int last_wildcard_question_mark_index = -1;
    for (int i = p_size - 1; i >= 0; --i) {
        if (p[i] == '?' && (i == 0 || p[i - 1] != '\\')) {
            last_wildcard_question_mark_index = i;
            break;
        }
    }

    std::vector<int> positions(256, last_wildcard_question_mark_index);

    int chars_escaped = 0;

    for (int i = 0; i < p_size; ++i) {
        if (p[i] == '\\' && i < p_size - 1) {
            i++;
            chars_escaped++;
        }
        positions[p[i]] = i;
    }

    int t_index = 0;
    while (t_index <= t_size - p_size + chars_escaped) {
        int p_index = 0;

        int delta = 0;

        while (p_index < p_size) {
            char current_text_char = t[t_index + p_index - delta];
            char current_pattern_char = p[p_index];
            bool escaped = false;

            if (p[p_index] == '\\') {
                delta++;
                p_index++;
                current_pattern_char = p[p_index];
                escaped = true;
            }

            if (current_text_char == current_pattern_char ||
                !escaped && current_pattern_char == '?') {
                p_index++;
                continue;
            }

            break;
        }

        if (p_index >= p_size) {
            return {true, t_index, t_index + p_size - chars_escaped};
        } else {
            int shift = p_index - positions[t[t_index + p_index]];

            if (shift > 0) {
                t_index += shift;
            } else {
                ++t_index;
            }
        }
    }

    return {false, -1, -1};
}

//bool WildcardSundayPatternMatchingAlgorithm::find_match(const std::string &t, const std::string &pattern) {
//    std::string p = pattern;
//
//    size_t t_size = t.size();
//    size_t p_size = p.size();
//
//    // Check if pattern has correct format, e.g. after backslash is a wildcard or another backslash
//    if (p_size == 1 && p[0] == '\\') {
//        throw std::logic_error("Pattern is incorrect. Invalid sequence at index 0: \\");
//    }
//    for (int i = 0; i < p_size; ++i) {
//        if (p[i] == '\\') {
//            if (i < p_size - 1) {
//                if (p[i + 1] == '*' || p[i + 1] == '?' || p[i + 1] == '\\') {
//                    i++;
//                } else {
//                    throw std::logic_error("Pattern is incorrect. Invalid sequence at index " + std::to_string(i) + ": "
//                                           + std::string(1, p[i]) + std::string(1, p[i + 1]));
//                }
//            }
//            if (i == p_size - 1 && p_size >= 1 && p[i - 1] != '\\') {
//                throw std::logic_error(
//                        "Pattern is incorrect. Invalid sequence at index " + std::to_string(i) + ": \\");
//            }
//        }
//    }
//
//    // Preprocess pattern to merge duplicate stars which are next to each other
//    std::stringstream new_p;
//    for (int i = 0; i < p_size; ++i) {
//        if (p[i] == '*') {
//            int j = i + 1;
//            while (j < p_size && p[j] == '*') {
//                j++;
//            }
//            i = j - 1;
//        }
//        new_p << p[i];
//    }
//    p = new_p.str();
//    // Trim star from start
//    if (p[0] == '*') {
//        p = p.substr(1);
//    }
//    // Trim star from end if not escaped
//    if (p.size() > 1 && p[p.size() - 1] == '*' && p[p.size() - 2] != '\\') {
//        p = p.substr(0, p.size() - 1);
//    }
//    p_size = p.size();
//
//    // If pattern is empty, then trivial
//    if (p_size == 0) {
//        return true;
//    }
//
//    int text_cursor = 0;
//    int pattern_cursor = 0;
//
//    int index_of_first_star = find_next_star_index(p, 0);
//    if (index_of_first_star >= 0) {
//        Match initial_match = find_match_without_star(t, p.substr(0, index_of_first_star));
//        if (!initial_match.found) {
//            return false;
//        }
//        text_cursor = initial_match.end_index;
//        pattern_cursor = index_of_first_star;
//    } else {
//        return find_match_without_star(t, p).found;
//    }
//
//    while (pattern_cursor < p_size) {
//        // End of the text reached, pattern not found yet
//        if (text_cursor >= t_size) {
//            break;
//        }
//
//        int index_of_next_star = find_next_star_index(p, pattern_cursor + 1);
//        // This is the last star in the pattern
//        if (index_of_next_star == -1) {
//            // No more pattern characters after it, so trivial
//            if (pattern_cursor == p_size - 1) {
//                return true;
//            }
//                // Check if there is a match in the rest of the pattern
//            else {
//                return find_match_without_star(t.substr(text_cursor), p.substr(pattern_cursor + 1)).found;
//            }
//        }
//            // There is another star in the pattern
//        else {
//            std::string text_to_match = t.substr(text_cursor);
//            std::string pattern_to_match = p.substr(pattern_cursor + 1, index_of_next_star - pattern_cursor - 1);
//            Match match_between = find_match_without_star(text_to_match, pattern_to_match);
//            if (!match_between.found) {
//                return false;
//            }
//            pattern_cursor = index_of_next_star;
//            text_cursor += match_between.end_index;
//        }
//
//        // Last pattern star reached, and it is at the last index, so trivial
//        if (pattern_cursor == p_size - 1) {
//            return true;
//        }
//    }
//
//    return false;
//}

std::string WildcardSundayPatternMatchingAlgorithm::get_name() { return "Wildcard Sunday"; }