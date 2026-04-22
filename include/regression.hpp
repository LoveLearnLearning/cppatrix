#ifndef REGRESSION_HPP_
#define REGRESSION_HPP_

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

    template<typename T>
    T MSE(Matrix<T> &x_t, Matrix<T> &y_t, Matrix<T> &w, Matrix<T> &b) {
        double diff = 0.f;
        double cost = 0.f;

        for (size_t i = 0; i < x_t.rows; ++i) {
            double y_p = func::sigmoidf2((w * x_t.row_view()[i].transpose() + b)(0, 0));
            diff += pow(y_t(i, 0) - y_p, 2);
        }
        return diff / x_t.rows;
    }

    template<typename T>
    Matrix<T> dMSE(Matrix<T> &x_t, Matrix<T> &y_t, Matrix<T> &w, Matrix<T> &b, double l_r = 1e-3) {

        Matrix<double> grad(x_t.row_view()[0].cols, x_t.row_view()[0].rows);
        Matrix<double> d(x_t.row_view()[0].cols, x_t.row_view()[0].rows);

        for (size_t n = 0; n < 1000; ++n) {
            for (size_t i = 0; i < x_t.rows; ++i) {
                d += x_t.row_view()[i].transpose() * (w * x_t.row_view()[i].transpose() + b)(0, 0);
            }

            grad = d * (2.0 / x_t.rows);
            w -= grad.transpose() * l_r;
        }
        return w;
    }

}

#endif //REGRESSION_HPP_
