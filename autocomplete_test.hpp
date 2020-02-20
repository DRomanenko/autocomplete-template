
using namespace std;

int rnd(int m) {
    return (static_cast<int>(mt19937(random_device()())()) % m + m) % m;
}

char choose_char(int range) {
    return static_cast<char>('a' + (rnd(range)));
}

string choose_string(int len, int range) {
    string res;
    int res_len = rnd(len) + 1;
    for (int i = 0; i < res_len; ++i) {
        res += choose_char(range);
    }

    return res;
}

namespace test {
    const int MAX_TEST_QTY = 50, MAX_N = 2e4 + 7;
    vector<term> coll, res_calc, res_run;
    size_t qty_run;
    string prefix;
    bool passing = true;

    void gen_test (int passed) {
        // cout << "Running test " << passed << '\n';
        int magic = passed / 20 + 1;
        int qty = min(MAX_N, ((magic << ((3 * passed) / 25))));
        int len = min(MAX_N / qty, (rnd(passed * passed * magic) + 1));
        int range = min(magic * 8, 'z' - 'a' + 1);

        // cout << magic << ' ' << qty << ' ' << len << ' ' << range << '\n';

        coll.clear();
        coll.reserve(qty);
        for (int i = 0; i < qty; ++i) {
            coll.emplace_back(choose_string(len, range), rnd(magic * 500));
            // cout << coll.back().get_query() << ' ' << coll.back().get_weight() << '\n';
        }

        prefix = choose_string(len, range);
    }

    void calculate() {
        // cout << "calculating\n";
        res_calc.clear();
        for (auto &i : coll) {
            bool satisfy = true;
            string s = i.get_query();
            for (size_t pos = 0; pos < prefix.length() && satisfy; ++pos) {
                satisfy = satisfy && (s[pos] == prefix[pos]);
            }

            if (satisfy)
                res_calc.emplace_back(i);
        }
        // cout << "calculated\n";
    }

    void run() {
        // cout << "running\n";
        autocomplete a(coll);
        res_run = a.all_matches(prefix);
        qty_run = a.number_of_matches(prefix);
        // cout << "run\n";
    }

    void show_test() {
        cout << "\nAll info would be in test_log.txt\n";
        ofstream out("test_log.txt");

        out << "prefix: " << prefix << '\n';
        out << "===== TEST =====\n";
        for (auto &i : coll) {
            out << i << '\n';
        }

        out << "=== EXPECTED ===\n";
        for (auto &i : res_calc) {
            out << i << '\n';
        }

        out << "=== USER ANS ===\n";
        for (auto &i : res_run) {
            out << i << '\n';
        }
        passing = false;
    }

    void validate(int passed) {
        if (qty_run != res_run.size()) {
            cout << "all_matches and number_of_matches returns different result\n"
                    "all_matches size: " << res_run.size() <<
                 ", number_of_matches: " << qty_run <<
                 "\nexpected: " << res_calc.size();

            show_test();
            return;
        }

        if (res_run.size() != res_calc.size()) {
            cout << "expected result size is " << res_calc.size() <<
                 ", but found " << res_run.size();
            show_test();
            return;
        }

        sort(res_run.begin(), res_run.end(), term::by_prefix_order());
        sort(res_calc.begin(), res_calc.end(), term::by_prefix_order());
        for (size_t pos = 0; pos < res_calc.size(); ++pos) {
            if (res_calc[pos] != res_run[pos]) {
                cout << "expected " << res_calc[pos] << " after sorting process, but found " << res_run[pos];
                show_test();
                return;
            }
        }

        if (passed % 10 == 0) {
            cout << passed << " tests completed out of " << MAX_TEST_QTY << '\n';
        }
    }

    void check (int passed) {
        gen_test(passed);
        run();
        calculate();
        validate(passed);
    }
}