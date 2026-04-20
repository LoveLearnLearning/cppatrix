#include "../include/functions.hpp"
#include <cmath>
#include <random>


double func::sigmoidf2(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double func::randf(double down, double top) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist_real(down, top);

    return dist_real(gen);
}
