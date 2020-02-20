#include <string>

class term {
public:
    /*** Default constructor. ***/
    term () : query(""),
              weight(0) {}

    /*** Assignment constructor ***/
    term (std::string query, int weight) : query(std::move(query)),
                                           weight(weight) {}

    /*** Copy constructor. ***/
    term (const term &other) : query(other.query),
                               weight(other.weight) {}

    std::string get_query () {
        return this->query;
    }

    int get_weight () {
        return this->weight;
    }

    term &operator= (const term &other) {
        if (this == &other) {
            return *this;
        }
        query = other.query;
        weight = other.weight;
        return *this;
    }

    bool operator== (const term &other) const {
        return query == other.query && weight == other.weight;
    }

    friend bool operator< (const term &t_1, const term &t_2) {
        return t_1.query == t_2.query ? t_1.weight < t_2.weight : t_1.query < t_2.query;
    }

    friend bool operator> (const term &t_1, const term &t_2) {
        return t_1.query == t_2.query ? t_1.weight > t_2.weight : t_1.query > t_2.query;
    }

    bool operator!= (const term &other) const {
        return !(*this == other);
    }

    std::string to_string () const {
        return std::to_string(weight) + " " + query;
    }

    friend std::ostream &operator<< (std::ostream &out_stream, const term &t) {
        return out_stream << t.to_string();
    }

    struct reverse_weight_order_functor {
        bool operator() (term const &t_1, term const &t_2) {
            return t_1.weight > t_2.weight;
        }
    };

    static reverse_weight_order_functor by_reverse_weight_order () {
        return reverse_weight_order_functor{};
    }

    struct prefix_order_functor {
        int prefix_len;

        prefix_order_functor (int new_len) : prefix_len(new_len) {}

        bool operator() (term const &t_1, term const &t_2) {
            //std::cout << t_1 << ' ' << t_2 << '\n';
            int len_t_1 = t_1.query.length(), len_t_2 = t_2.query.length();
            int min_len = std::min(prefix_len < 0 ? INT32_MAX : prefix_len, std::min(len_t_1, len_t_2));
            for (int i = 0; i < min_len; ++i) {
                if (t_1.query[i] != t_2.query[i]) {
                    return t_1.query[i] < t_2.query[i];
                }
            }
            return prefix_len < 0 ? len_t_1 < len_t_2 : false;
        }
    };

    static prefix_order_functor by_prefix_order (int new_len = -1) {
        return prefix_order_functor{new_len};
    }

private:
    std::string query;
    int weight;
};