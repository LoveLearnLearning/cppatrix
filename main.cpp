#include "./include/matrix.hpp"
#include "./include/regression.hpp"

#include <cstdlib>
#include <iostream>

int main() {
    double w1 = (double)rand();
    double w2 = (double)rand();



    Matrix<double> weight = {
        {w1 ,w2}
    };

    Matrix<double> para = {
        {0},
        {1}
    };

    Matrix<double> b = {
        {0}
    };

    Matrix<double> y = {
        {0}
    };


    Matrix<double> predict = reg::forward(para, weight, b);
    Matrix<double> cost = reg::cost(predict, y);

    std::cout << cost << std::endl;

}
