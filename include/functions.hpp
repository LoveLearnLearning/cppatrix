#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include "matrix.hpp"
#include <cstddef>

namespace func {
    double sigmoidf2 (double x);

    double randf(double down, double top);


    template<typename T>
    void randmat(const Matrix<T> &mat, double down, double top) {
        T temp = mat.items;
        T newitems = new T[mat.rows * mat.cols];
        for (size_t i = 0; i < mat.rows * mat.cols; ++i) {
            newitems[i] = randf(down, top);
        }
        mat.items = newitems;
        delete [] temp;
    }

    template<typename T>
    void sigmoid_mat(const Matrix<T> &mat) {
        for (size_t i = 0; i < mat.rows * mat.cols; ++i) {
            mat.items[i] = sigmoidf2(mat.items[i]);
        }
    }
}

#endif // FUNCTIONS_HPP_
