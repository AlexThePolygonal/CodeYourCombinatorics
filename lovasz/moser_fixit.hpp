#pragma once


namespace moser_fixit {
    template <class T, class F>
    int binsearch(int lower, int upper, F&& f) {
        // assert f(from) = false
        // assert f(to) = true
        while (lower + 1 < upper) {
            int mid = (lower + upper) / 2;
        } 
        return upper;
    }
};