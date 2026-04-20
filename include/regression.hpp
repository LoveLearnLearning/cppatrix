#ifndef REGRESSION_H_
#define REGRESSION_H_

#include "matrix.hpp"
#include "functions.hpp"

#include <cstddef>

namespace reg {

    template<typename T>
    Matrix<T> forward(const Matrix<T> &params, const Matrix<T> &weight, const Matrix<T> &bais) {
        return weight * params + bais;
    }

    template<typename T>
    T MSE(const Matrix<T> &X, const Matrix<T> &Y, const Matrix<T> &weight, const Matrix<T> &bias) {
        T diff = 0;
        for (Matrix<T> row : X) {

        }

    }
    template<typename T>
    void dMSE() {}


    template<typename T>
    void fill_random(Matrix<T> &mat) {
        for (size_t i = 0; i < mat.rows; ++i) {
            for (size_t j = 0; j < mat.cols; ++j) {
                mat(i, j) = func::randf(0.0, 1.0);
            }
        }
    }
}

#endif //REGRESSION_H_
