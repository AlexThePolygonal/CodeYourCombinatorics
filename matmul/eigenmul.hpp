#pragma once
#include <Eigen/Core>
#include <iostream>
#include <random>




namespace is_prod_eq {
 
namespace lib_naive {
template <class Scalar>
bool basic(Eigen::MatrixX<Scalar>& A, 
                Eigen::MatrixX<Scalar>& B, 
                Eigen::MatrixX<Scalar>& C) noexcept {
    return C == A*B;
}
};


namespace hand_matousek {

template <class Scalar>
struct Matrix {
    size_t rows;
    size_t cols;
    Scalar* ptr;
    Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols), ptr(new Scalar[rows * cols]) {}
    Scalar& operator()(size_t i, size_t j) noexcept { return ptr[i*cols + j];}
    const Scalar& operator()(size_t i, size_t j) const noexcept { return ptr[i*cols + j];}


    Matrix(const Matrix& other) : Matrix(other.rows, other.cols) {
        for (size_t i = 0; i < other.rows * other.cols; i++) {
            ptr[i] = other.ptr[i];
        }
    }
    Matrix(Matrix&& other) : rows(other.rows), cols(other.cols), ptr(other.ptr) {
        other.ptr = nullptr;
    }
    Matrix& operator=(const Matrix& other) {
        delete ptr;
        rows = other.rows;
        cols = other.cols;
        ptr = new Scalar(rows*cols);
        for (size_t i = 0; i < other.rows * other.cols; i++) {
            ptr[i] = other.ptr[i];
        }
        return &this;
    }
    Matrix& operator=(Matrix&& other) {
        rows = other.rows;
        cols = other.cols;

        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    ~Matrix() { delete ptr; }
    Matrix(const Eigen::MatrixX<Scalar> other) : Matrix(other.rows(), other.cols()) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                this->operator()(i, j) = other(i, j);
            }
        }

    }
    
    std::vector<Scalar> mul(const std::vector<Scalar>& v) const noexcept {
        const Matrix<Scalar>& mat = *this;
        std::vector<Scalar> res(rows, 0);

        for (size_t i = 0; i < rows; i++) {
            Scalar& val = res[i];

            for (size_t j = 0; j < cols; j++) {
                val += mat(i, j) * v[j];
            }
        }
        return res;
    };
};

template <class Scalar>
std::vector<Scalar> random_01_vec(size_t size) {
    std::vector<Scalar> res(size, 0);
    std::random_device rd;
    std::mt19937 gen(rd());    
    std::bernoulli_distribution bern(0.5);

    for (size_t i = 0; i < size; i++) {
        res[i] = bern(gen);
    }
    return res;
}

template <class Scalar>
bool equal(const std::vector<Scalar>& a, const std::vector<Scalar>& b) {
    static_assert(!std::is_floating_point_v<Scalar>);
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

template <class Scalar>
bool basic(Matrix<Scalar>& A, 
            Matrix<Scalar>& B, 
            Matrix<Scalar>& C, 
            size_t tol = 10u) noexcept {
    for (size_t i = 0; i < tol; i++) {
        auto randv = random_01_vec<int>(B.rows);
        if (!equal(C.mul(randv), A.mul(B.mul(randv)))) {
            return false;
        }
    }
    return true;
}
};

};

