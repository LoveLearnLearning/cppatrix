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
    T forward(Matrix<T> &row, T w) {
        return w * row(0, 0);
    }

    template<typename T>
    T MSE(Matrix<T> &train, T w) {
        double diff = 0.f;
        double cost = 0.f;

        for (auto row : train.row_view()) {
            diff += pow(forward(row, w) - row(0, 1), 2);
            cost = diff / train.rows;
        }
        return cost;
    }

    template<typename T>
    T dMSE(Matrix<T> &train, T w, double l_r = 1e-3) {
        double gradient = 0.f;
        double diff = 0.f;
        for (auto row : train.row_view()) {
            diff += (w * row(0, 0) - row(0, 1)) * row(0, 0);
        }
        gradient = 2 * diff / train.rows;
        return w - l_r * gradient;
    }


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
