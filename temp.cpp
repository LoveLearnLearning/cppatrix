#include "include/matrix.hpp"
#include <iostream>



int main() {

    Matrix<double> mat1 = {
        {1, 2, -1},
        {2, 1, -3},
    };


    Matrix<double> mat2 = {
        {1, 3},
        {-1, 1},
        {2, -1},
    };

    Matrix<double> mat4 = {
        {1, 0, -1},
        {2, -1, -3},
    };

    auto mat3 = mat1 * mat2;


    auto mat6 = mat5.take_block(0, 0, 1, 1);

    std::cout << mat3;

}
