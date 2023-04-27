#include "sol.hpp"


namespace groupoids {
struct triple {
    int a,b,c;
};


class Trivial : public assoc::Groupoid {
public:
    int c;
    Trivial(size_t n, int c_) {
        size = n;
        c = c_;
    }
    int operator()(int a, int b) const noexcept override {
        return c;
    }
};


class Tripleless : public assoc::Groupoid {
public:
    Tripleless(size_t size_, std::vector<triple> vec) {
        size = size_;
    }
    int operator()(int a, int b) const noexcept override {
    }
};
class ZnZ : public assoc::Groupoid {
public:
    ZnZ(size_t n) {
        size = n;
    }
    int operator()(int a, int b) const noexcept override {
        return (a + b)%size;
    }
};

template <class F, class G>
class Prod : public assoc::Groupoid {
public:
    F f;
    G g;
    Prod(F&& f_, G&& g_) : f(f_), g(g_) {
        size = f.size * g.size;
    }
    int operator()(int a, int b) const noexcept override {
        return f(a/g.size, b/g.size)*g.size + g(a%g.size, b%g.size);
    };
};

class BasedonZnZ: public assoc::Groupoid {
public:
    int a;
    int b;
    BasedonZnZ(size_t n, int b_/*b_!=0, b_!=n*/) {
        size = 2*n;
        a = n;
        b = b_;
    }
    int operator()(int x, int y) const noexcept override {
        if ((x!=b && x!=((a+b)%size)) || (y!=b && y!=((a+b)%size))) {
            return (x + y)%size;
        }
        if (x == b && y == b) {
            return (2*b + a) % size;
        }
        if (x == (a+b)%size && y == (a+b)%size) {
            return (2*b + a) % size;
        }
        if (x == b && y == (a+b)%size) {
            return (2*b) % size;
        }
        if (y == b && x == (a+b)%size) {
            return (2*b) % size;
        }
    }
};
};


template <class F>
class Modded : assoc::Groupoid {
public:
    F f;
    std::vector<triple> v;
    template <class ... Args>
    Modded(std::vector<triple> arg, Args&&... args) : f(std::forward<Args>(args)...), v(args) {};

    int operator()(int x, int y) const noexcept override {
        for (auto t : v) {
            if (x == t.a && y == t.b) {
                return t.c;
            }
        }
        return f(x,y);
    };
};

template <class F>
class Permuted : assoc::Groupoid {
    
    Permuted()
};

int main() {

}