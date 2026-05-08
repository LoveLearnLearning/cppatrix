#ifndef REGRESSION_HPP_
#define REGRESSION_HPP_

#include "matrix.hpp"
#include "functions.hpp"

#include <cstddef>

namespace reg {

    template<typename T>
    mat::Matrix<T> forward(const mat::Matrix<T> &params, const mat::Matrix<T> &weight, const mat::Matrix<T> &bais) {
        return weight * params + bais;
    }

    template<typename T>
    T forward(mat::Matrix<T> &row, T w) {
        return w * row(0, 0);
    }

    template<typename T>
    T MSE(mat::Matrix<T> &train, T w) {
        double diff = 0.f;
        double cost = 0.f;

        for (auto row : train.row_view()) {
            diff += pow(forward(row, w) - row(0, 1), 2);
            cost = diff / train.rows;
        }
        return cost;
    }

    template<typename T>
    T dMSE(mat::Matrix<T> &train, T w, double l_r = 1e-3) {
        double gradient = 0.f;
        double diff = 0.f;
        for (auto row : train.row_view()) {
            diff += (w * row(0, 0) - row(0, 1)) * row(0, 0);
        }
        gradient = 2 * diff / train.rows;
        return w - l_r * gradient;
    }


    template<typename T>
    void fill_random(mat::Matrix<T> &mat) {
        for (size_t i = 0; i < mat.rows; ++i) {
            for (size_t j = 0; j < mat.cols; ++j) {
                mat(i, j) = func::randf(0.0, 1.0);
            }
        }
    }

    template<typename T>
    T MSE(mat::Matrix<T> &x_t, mat::Matrix<T> &y_t, mat::Matrix<T> &w, mat::Matrix<T> &b) {
        T diff = 0.f;
        T cost = 0.f;

        for (size_t i = 0; i < x_t.rows; ++i) {
            T y_p = func::sigmoidf2((w * x_t.row_view()[i].transpose() + b)(0, 0));
            diff += pow(y_t(i, 0) - y_p, 2);
        }
        return diff / x_t.rows;
    }

    template<typename T>
    mat::Matrix<T> dMSE(mat::Matrix<T> &x_t, mat::Matrix<T> &y_t, mat::Matrix<T> &w, mat::Matrix<T> &b, double l_r = 1e-3) {

        mat::Matrix<T> grad(x_t.row_view()[0].cols, x_t.row_view()[0].rows);
        mat::Matrix<T> d(x_t.row_view()[0].cols, x_t.row_view()[0].rows);


        for (size_t i = 0; i < x_t.rows; ++i) {
            mat::Matrix<T> x = x_t.row_view()[i].transpose();
            T forward = (w * x_t.row_view()[i].transpose() + b)(0, 0);
            d +=  x * func::sigmoidf2(forward)
                    * (1 - func::sigmoidf2(forward))
                    * (func::sigmoidf2(forward) - y_t(i, 0));
        }

        grad = d * (2.0 / x_t.rows);
        w -= grad.transpose() * l_r;

        return w;
    }

}

#endif //REGRESSION_HPP_
