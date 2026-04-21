#include "./include/matrix.hpp"
#include "./include/functions.hpp"
#include "regression.hpp"

#include <cstddef>
#include <cstdlib>
#include <print>


int main() {

    Matrix<double> train = {
        {1, 2},
        {2, 4},
        {3, 6},
        {4, 8},
        {5, 10},
    };

    double w = func::randf(1, 10);

    std::println("WeightBefore: {}", w);
    std::println("Cost: {}", reg::MSE(train, w));

    for (size_t i = 0; i < 1000; ++i) {
        w = reg::dMSE(train, w, 1e-3);
        std::println("Cost: {}", reg::MSE(train, w));
    }

    for (auto row : train.row_view()) {
        std::println("{} -> {} : {}", row(0, 0), reg::forward(row, w), row(0, 1));
    }

    std::println("WeightAfter: {}", w);
    std::println("Cost: {}", reg::MSE(train, w));

}
