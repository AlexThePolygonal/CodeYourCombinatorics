#include <iostream>
#include "eigenmul.hpp"
#include <exception>
#include <chrono>
#include "../assist/niceties.hpp"

#define ASSERT(expr) { if (!(expr)) throw std::runtime_error("assertion failed");}

void CompileTest() {
    Eigen::MatrixX<int> B = Eigen::MatrixX<int>::Zero(2,2);
    Eigen::MatrixX<int> A = Eigen::MatrixX<int>::Zero(2,2);
    A << 1,2,3,-4;
    B << 1,-1,2,5;
    Eigen::MatrixX<int> C = A * B;
    C(1,1) += 1;
    ASSERT(!is_prod_eq::lib_naive::basic(A, B, C))
    is_prod_eq::hand_matousek::Matrix<int> _A(A), _B(B), _C(C);
    ASSERT(!is_prod_eq::hand_matousek::basic(_A, _B, _C))    
}



void GrandTest() {

    int size = 4000;
    Eigen::MatrixX<int> A = (Eigen::MatrixX<float>::Random(size,size) * 10).cast<int>();
    Eigen::MatrixX<int> B = (Eigen::MatrixX<float>::Random(size,size) * 10).cast<int>();
    Eigen::MatrixX<int> C  = A*B;
    
    std::random_device rd;
    std::mt19937 gen(rd());    
    std::bernoulli_distribution bern(0.5);
    std::uniform_int_distribution intdistr(0, size-1);
    if (bern(gen)) {
        C(intdistr(gen), intdistr(gen)) += 1;
    }


    {
        auto start = std::chrono::steady_clock::now();
        std::cout << is_prod_eq::lib_naive::basic(A, B, C) << '\n';
        std::cout << "Elapsed(ms)=" << aux::since(start).count() << std::endl;
    }
    using Matrix = is_prod_eq::hand_matousek::Matrix<int>;
    {   
        Matrix _A(A), _B(B), _C(C);
        auto start = std::chrono::steady_clock::now();
        std::cout << is_prod_eq::hand_matousek::basic(_A, _B, _C) << '\n';
        std::cout << "Elapsed(ms)=" << aux::since(start).count() << std::endl;
    }
}



int main() 
{
    std::srand((unsigned int) time(0));
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::boolalpha;
    CompileTest();
    GrandTest();
    GrandTest();
    GrandTest();
}