#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include "matrix.hpp"
#include <cstddef>

namespace func {
    double sigmoidf2 (double x);

    double randf(double down, double top);


    template<typename T>
    void randmat(mat::Matrix<T> &mat, double down, double top) {
        T *temp = mat.items;
        T *newitems = new T[mat.rows * mat.cols];
        for (size_t i = 0; i < mat.rows * mat.cols; ++i) {
            newitems[i] = randf(down, top);
        }
        mat.items = newitems;
        delete [] temp;
    }

    template<typename T>
    void sigmoid_mat(const mat::Matrix<T> &mat) {
        for (size_t i = 0; i < mat.rows * mat.cols; ++i) {
            mat.items[i] = sigmoidf2(mat.items[i]);
        }
    }

    template<typename T>
    T dist(mat::Matrix<T> &mat1, mat::Matrix<T> &mat2) {
        if (mat1.rows != 1 && mat2.rows != 1 && mat1.cols != mat2.cols) {
            throw std::invalid_argument("Distance dimension do not match!");
        }
        double sum = 0.f;
        for (size_t i = 0; i < mat1.cols; ++i) {
            sum += pow((mat1(0, i) - mat2(0, i)), 2);
        }
        return pow(sum, 1 / mat1.cols);
    }
}

#endif // FUNCTIONS_HPP_
