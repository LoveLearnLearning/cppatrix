#include "functions.hpp"
#include "matrix.hpp"
#include "regression.hpp"
#include <cstddef>
#include <iostream>

int main() {
    Matrix<double> train = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {1, 1, 1},
    };

    Matrix<double> w(1, 2);
    Matrix<double> b(1, 1);

    func::randmat(w, 0, 10);
    func::randmat(b, 0, 10);

    Matrix<double> x_t = train.take_block(0, 0, 3, 1);
    Matrix<double> y_t = train.take_block(0, 2, 3, 2);

    double cost = reg::MSE(x_t, y_t, w, b);

    std::cout << "w: " << w << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "Cost: " << cost << std::endl;

    double l_r = 1e-3;
    Matrix<double> grad(x_t.row_view()[0].cols, x_t.row_view()[0].rows);
    Matrix<double> d(x_t.row_view()[0].cols, x_t.row_view()[0].rows);


    for (size_t n = 0; n < 1000 * 10000; ++n) {
        w = reg::dMSE(x_t, y_t, w, b, l_r);
        cost = reg::MSE(x_t, y_t, w, b);
        std::cout << "Cost: " << cost << std::endl;
    }
    std::cout << "Gradient: " << grad << std::endl;
    std::cout << "w: " << w << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "Cost: " << cost << std::endl;


}
