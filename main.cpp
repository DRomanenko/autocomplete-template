#include <random>
#include <fstream>
#include <cassert>
#include "autocomplete.hpp"
#include "autocomplete_test.hpp"

int main () {
    cout << "General tests:\n";
    term t_0("ztnsbd", 25), t_1("zzzzz", 70), t_2("ztnsbd", 25);
    cout << "Test 1 (to_string and operator <<):\n";
    std::cout << t_0.to_string() << '\n' << t_1 << '\n' << t_2.to_string() << '\n';
    std::cout << "-----------------\n";
    cout << "Test 2 (operator ==):\n";
    assert(t_0 == t_2);
    std::cout << "Passed!\n-----------------\n";
    cout << "Test 3 (operator !=):\n";
    assert(t_1 != t_2);
    std::cout << "Passed!\n-----------------\n";
    cout << "Test 4 (by_reverse_weight_order):\n";
    assert(term::by_reverse_weight_order()(t_1, t_2));
    std::cout << "Passed!\n-----------------\n";
    cout << "Test 5 (by_prefix_order):\n";
    assert(!term::by_prefix_order()(t_1, t_2));
    std::cout << "Passed!\n-----------------\n";

    cout << "Test 6 (Autocomplete : number_of_matches):\n";
    std::vector<term> terms;
    terms.emplace_back("путин краб", 40);
    terms.emplace_back("где поесть", 20);
    terms.emplace_back("где логика", 10);
    terms.emplace_back("скачать бесплатно без смс", 50);
    terms.emplace_back("где посылка", 30);
    terms.emplace_back("", 114514);
    autocomplete a(terms);
    assert(a.number_of_matches("где") == 3);
    a.print(a.all_matches("где"));
    std::cout << "Passed!";
    cout << "\n-----------------\nGeneral tests finished!\n\n";


    cout << "\nTest 7-1000 (small tests)";
    for (int num = 1; num <= 993 && test::passing; ++num) {
        test::check(8);
    }
    std::cout << "\nPassed!\n";

    cout << "\nTest 1001-1050 (big random tests):\n";
    for (int num = 1; num <= test::MAX_TEST_QTY && test::passing; ++num) {
        test::check(num);
    }
    std::cout << "Passed!\n-----------------\nAll tests finished!\n\n";

    return 0;
}