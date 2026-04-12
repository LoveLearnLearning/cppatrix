#ifndef REGRESSION_H_
#define REGRESSION_H_

#include "matrix.hpp"

#include <cstddef>
#include <vector>

namespace reg {

    double sigmoidf2 (double x);

    template<typename T>
    void sigmoid_mat(const Matrix<T> &mat) {
        for (size_t i = 0; i < mat.rows * mat.cols; ++i) {
            mat.items[i] = sigmoidf2(mat.items[i]);
        }
    }

    template<typename T>
    Matrix<T> forward(const Matrix<T> &params, const Matrix<T> &weight, const Matrix<T> &bais) {
        return weight * params + bais;
    }

    template<typename T>
    T MSE(const std::vector<std::vector<T>> &data, const Matrix<T> &weight, const Matrix<T> &bias) {
        T diff = 0;

        for (const std::vector<T>& param : data) {
            Matrix<T> input = {
                {param[0]},
                {param[1]}
            };
            Matrix<T> expect = {
                {param[2]}
            };

            Matrix<T> real = forward<T>(input, weight, bias);
            sigmoid_mat(real);

            diff += ((expect - real)(0, 0) * (expect - real)(0, 0));

        }

        return diff / data.size();
    }

}

#endif //REGRESSION_H_
