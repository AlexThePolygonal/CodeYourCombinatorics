#pragma once
#include <algorithm>
#include <chrono>

namespace aux {
    template <class Scalar>
    Scalar Abs(const Scalar& v) { return (v>=0 ? v: -v);}


    template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
    >
    auto since(std::chrono::time_point<clock_t, duration_t> const& start)
    {
        return std::chrono::duration_cast<result_t>(clock_t::now() - start);
    }

    template <class F>
    auto timeit(F&&f) {
        auto start = std::chrono::steady_clock::now();
        auto res = f();
        auto elapsed = aux::since(start).count();
        return std::pair(res, elapsed);
    }

    auto range(size_t n) {
        struct Iterator {
            size_t cur = 0;
            size_t& operator++() { return ++cur; }
            size_t& operator*() {return cur;}
            bool operator!=(size_t end) {
                return cur < end;
            }
        };
        struct RangeStruct {
            size_t n;
            auto begin() { return Iterator(); }
            auto end() { return n;}
        } res;
        res.n = n;
        return res;
    }

    template <class F>
    class defer {
        F f;
    public:
        defer(F&&_f) : f(std::move(_f)) {}
        ~defer() {
            f();
        }
    };
};