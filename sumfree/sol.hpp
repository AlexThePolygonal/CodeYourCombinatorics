#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../assist/niceties.hpp"
#include "../assist/primegen.hpp"
#include <ctgmath> 


namespace sumfree_sols {
    template <class Scalar>
    bool verify_sumfreeness(const std::vector<Scalar>& v) {
        std::unordered_set<Scalar> set(v.begin(), v.end());
        for (auto a : v) {
            for (auto b : v) {
                if (set.contains(a + b)) {
                    return false;
                }
            }
        }
        return true;
    }

    template <class Scalar>
    std::vector<Scalar> greedy(const std::vector<Scalar>& list) {
        std::unordered_map<Scalar, bool> banned;
        std::unordered_set<Scalar> chosens;

        for (size_t i = 0; i < list.size(); i++) {
            if (!banned[list[i]]) {
                Scalar cur = list[i];

                bool can_insert = true;
                for (auto v : chosens) {
                    if (chosens.contains(cur + v)) {
                        can_insert = false;
                        break;
                    }
                }
                if (can_insert) {
                    chosens.insert(cur);
                    for (auto v : chosens) {
                        banned[v + cur] = true;
                    }
                }
            }
        }
        std::vector<Scalar> res;
        for (auto v : list) {
            if (chosens.contains(v)) {
                res.push_back(v);
            }
        }
        return res;
    }

    template <class Scalar>
    std::vector<Scalar> greedy_iterated(std::vector<Scalar>& list, size_t iters = 10) {
        for (auto _ : aux::range(iters)) {
            auto res = greedy(list);
            if (verify_sumfreeness(res) && res.size()*3 > list.size()) {
                return res;
            }
            std::random_shuffle(list.begin(), list.end());
        }   
        return {}; 
    }



    template <class Scalar>
    std::vector<Scalar> erdos_poly(std::vector<Scalar>& list) {

        long double l = 0;
        for (auto v : list) {
            l += log2l(aux::Abs(v));
        }

        Scalar prime_below = ceill(3 * l * logl(l)) + 100;
        
        
        auto sieve = primes::eratosthenes_sieve(prime_below);
        Scalar p = 0;


        for (Scalar i = 0; i < prime_below; i++) {
            bool is_a_divisor = false;
            if (sieve[i] && (i%3 == 2)) {
                for (auto v : list) {
                    if (v % i == 0) {
                        is_a_divisor = true;
                        break;
                    }
                }
                if (!is_a_divisor) {
                    p = i;
                    break;
                }
            }
        }
        Scalar k = (p-2)/3;
        
        Scalar prime_witness = 0;
        std::vector<Scalar> list_mod_p;
        list_mod_p.reserve(list.size());
        for (auto v : list) {
            list_mod_p.push_back((v >= 0 ? v : (v%p)+p ));
        }


        for (Scalar i = 1; i < p; i++) {
            size_t count = 0;
            
            for (auto v : list_mod_p) {
                Scalar vi = (v * i) % p;
                if (vi >= k+1 && vi <= 2*k+1) {
                    count++;
                }
            }
            if (count*3 >= list.size()) {
                prime_witness = i;
                break;
            }
        }
        std::vector<Scalar> res;
        for (size_t i = 0; i < list.size(); i++) {
            auto vi = (list_mod_p[i] * prime_witness) % p;
            if (vi >= k+1 && vi <= 2*k+1) {
                res.push_back(list[i]);
            }
        }
        return res;
    }
};

