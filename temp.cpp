#include "include/matrix.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>



int main() {
    Matrix<double> mat1 = {
        {1, 0, 0, 0, 5, 3, 0, 0, 1, 0, 0, 0}
    };

    Matrix<double> mat2 = {
        {3, 0, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 0}
    };

    double sum1 = [&]() -> double {
        double temp = 0.f;
        for (size_t i = 0; i < mat1.cols; ++i) temp += pow(mat1(0, i), 2);
        return sqrt(temp);
    }();

    double sum2 = [&]() -> double {
        double temp = 0.f;
        for (size_t i = 0; i < mat1.cols; ++i) temp += pow(mat2(0, i), 2);
        return sqrt(temp);
    }();

    mat1 *= (1 / sum1);
    mat2 *= (1 / sum2);

}
