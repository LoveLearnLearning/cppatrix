#include "include/matrix.hpp"
#include <iostream>


int main() {

    Matrix<int> mat1 = {
        {1, 2},
        {2, 1}
    };

    Matrix<int> mat3 = {
        {2, 4},
        {1, 3}
    };


    Matrix<int> mat2 = mat1 + mat3;

}
