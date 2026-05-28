#include "../include/functions.hpp"
#include "matrix.hpp"
#include <cmath>
#include <cstddef>
#include <random>

double func::sigmoidf2(double x) { return 1.0 / (1.0 + exp(-x)); }

double func::randf(double down, double top) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist_real(down, top);

    return dist_real(gen);
}

mat::Matrix<double> func::randmat(size_t r, size_t c, double down, double top) {
    mat::Matrix<double> result(r, c);
    for (size_t i = 0; i < r * c; ++i) {
        result.items[i] = randf(down, top);
    }
    return result;
}
