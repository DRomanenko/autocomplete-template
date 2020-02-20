#include <vector>
#include <functional>
#include <algorithm>

#include "term.hpp"

class binary_search_deluxe {
    typedef std::function<bool (term const &, term const &)> term_comparator;
public:
    static int first_index_of (std::vector<term> terms, const term &key, term_comparator comp) {
        /*std::cout << "in first_index_of\n";
        for (auto &i : terms) {
            std::cout << i << '\n';
        }
        std::cout << "key: " << key << '\n';*/
        return std::lower_bound(terms.begin(), terms.end(), key, std::move(comp)) - terms.begin();
    }

    static int last_index_of (std::vector<term> terms, const term &key, term_comparator comp) {
        /*std::cout << "in last_index_of\n";
        for (auto &i : terms) {
            std::cout << i << '\n';
        }
        std::cout << "key: " << key << '\n';*/

        return std::upper_bound(terms.begin(), terms.end(), key, std::move(comp)) - terms.begin() - 1;
    }

private:
    binary_search_deluxe() = default;
};