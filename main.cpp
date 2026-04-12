#include "./include/matrix.hpp"
#include "./include/regression.hpp"

#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {

    srand(1);
    double w1 = (double)rand();
    double w2 = (double)rand();
    double b1 = (double)rand();

    std::vector<std::vector<double>> data = {
        {0, 0, 0},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1}
    };


    Matrix<double> weight = {
        {w1 ,w2}
    };

    Matrix<double> b = {
        {b1}
    };

    double cost = reg::MSE<double>(data, weight, b);

    printf("Cost: %.6lf\n", cost);

}
