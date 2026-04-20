#include "matrix.hpp"

namespace func {
    double sigmoidf2 (double x);

    double randf(double down, double top);

    template<typename T>
    void sigmoid_mat(const Matrix<T> &mat) {
        for (size_t i = 0; i < mat.rows * mat.cols; ++i) {
            mat.items[i] = sigmoidf2(mat.items[i]);
        }
    }
}
