#ifndef REGRESSION_H_
#define REGRESSION_H_

#include "matrix.hpp"

namespace reg {
    template<typename T>
    Matrix<T> forward(Matrix<T> &params, Matrix<T> &weight, Matrix<T> &bais) {
        Matrix<T> mul = weight * params;
        Matrix<T> add = mul + bais;

        return add;
    }

    template<typename T>
    Matrix<T> cost(Matrix<T> &in, Matrix<T> &model) {
        return in - model;
    }

}

#endif //REGRESSION_H_
