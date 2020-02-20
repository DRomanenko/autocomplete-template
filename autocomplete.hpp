#include <iostream>

#include "binary_search_deluxe.hpp"

class autocomplete {
public:
    autocomplete (std::vector<term> &terms) : terms(terms) {
        std::sort(this->terms.begin(), this->terms.end(), term::by_prefix_order());
    }

    std::vector<term> all_matches (const std::string &prefix) {
        auto indices = find_bound(prefix);
        std::vector<term> matches;
        for (int i = indices.first; i <= indices.second; ++i) {
            matches.push_back(terms[i]);
        }
        std::sort(matches.begin(), matches.end(), term::by_reverse_weight_order());

        return matches;
    }

    int number_of_matches (const std::string &prefix) {
        auto indices = find_bound(prefix);
        return indices.second - indices.first + 1;
    }

    void print () {
        for (const term &t: terms) {
            std::cout << t << '\n';
        }
    }

    void print (const std::vector<term> &matches) {
        for (const term &t: matches) {
            std::cout << t << '\n';
        }
    }

private:
    std::vector<term> terms;

    std::pair<int, int> find_bound (const std::string &prefix) {
        using bsd = binary_search_deluxe;
        //std::cout << "first\n";
        int first = bsd::first_index_of(terms, term(prefix, 0), term::by_prefix_order());
        //std::cout << "second\n";
        int last = bsd::last_index_of(terms, term(prefix, 0), term::by_prefix_order(prefix.length()));
        return {first, last};
    }
};