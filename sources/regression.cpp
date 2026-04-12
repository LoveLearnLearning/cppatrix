#include "../include/regression.hpp"

#include <cmath>

double reg::sigmoidf2(double x) {
    return 1.f / (1.f + exp(-x));
}
