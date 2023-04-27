#include "sol.hpp"
#include <iostream>
#include "../assist/niceties.hpp"
#include "../assist/primegen.hpp"
#include <random>

template <class F>
auto RandomTest(F&& f) {
    std::vector<int64_t> vec;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-10000, 10000); // define the range
    for (auto _ : aux::range(20000)) {
        int v = distr(gen);
        if (v==0) {
            continue;
        }
        vec.push_back(v);
    }
    auto [seq, time] = aux::timeit([&](){ return f(vec);});
    bool is_passed = seq.size()*3 >= vec.size() && sumfree_sols::verify_sumfreeness(seq); 
    std::cout << is_passed << ' '<< time << std::endl;
    return is_passed;
}




int main() {
    std::cout << std::boolalpha;
    auto greedy = [](std::vector<int64_t>& vec) {
        return sumfree_sols::greedy_iterated(vec, 10);
    };
    auto erdos = [](std::vector<int64_t>& vec) {
        return sumfree_sols::erdos_poly(vec);
    };
    RandomTest(erdos);
    RandomTest(erdos);
    RandomTest(erdos);

}