#pragma once
#include "../assist/niceties.hpp"
#include "../assist/primegen.hpp"
#include <random>

namespace assoc {
    class Groupoid {
    public:
        size_t size;
        virtual int operator()(int, int) const noexcept = 0;
    };

    bool bruteforce(const Groupoid& g) {
        for (auto i : aux::range(g.size)) {            
        for (auto j : aux::range(g.size)) {            
        for (auto k : aux::range(g.size)) {            
            if (g(i,g(j, k)) != g(g(i,j),k)) {
                return false;
            }
        }
        }
        }
    }
    // probability of failure is <= 2^-31
    bool fieldsol(const Groupoid& g) {
        uint64_t p = 2147483647u;
        std::vector<uint32_t> u,v,w;
        u.reserve(g.size), v.reserve(g.size),w.reserve(g.size);

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<uint32_t> distr(0, p-1);


        for (auto _ : aux::range(g.size)) {
            u.push_back(distr(gen));
            v.push_back(distr(gen));
            w.push_back(distr(gen));
        }

        auto mul = [&g, p](const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
            std::vector<uint32_t> res(g.size, 0);
            for (auto i : aux::range(g.size)) {
            for (auto j : aux::range(g.size)) {
                uint64_t a_ = a[i];
                uint64_t b_ = b[i];
                res[g(i,j)] += (a_ * b_) % p;
            }
            }
            return res;
        };
        auto l = mul(mul(u, v), w);
        auto r = mul(u,mul(v, w));
        for (auto i : aux::range(g.size)) {
            if (l[i] != r[i]) {
                return false;
            }
        }
        return true;
    }
};