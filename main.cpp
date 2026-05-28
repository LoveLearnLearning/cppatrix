#include "clustering.hpp"
#include "matrix.hpp"
#include <iostream>

int main() {
    mat::Matrix<int> mat1 = {
        {1, 0, 0, 0},
        {2, 0, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 1, 0},
    };

    auto result = mat1 * mat1;
    std::cout << result << std::endl;
}
