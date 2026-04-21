#include "./include/matrix.hpp"
#include "./include/regression.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>


int main() {


    Matrix<double> data = {
        {0, 0, 0},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1}
    };

    // std::vector<std::vector<double>> data = {
    //     {1, 3, 0},
    //     {2, 2, 0},
    //     {3, 1, 0},
    //     {4, 2, 0},
    //     {5, 3, 0},
    //     {6, 4, 1},
    //     {7, 5, 1},
    //     {8, 6, 1},
    //     {9, 7, 1},
    //     {10, 8, 1}
    // };


    Matrix<double> block = data.take_block(1, 1, 4, 2);

    Matrix<double> new_block = block * 2;

    std::cout << block << std::endl;
    std::cout << new_block << std::endl;

    for (auto row : block.row_view()) {
        std::cout << row << std::endl;
    }

    for (auto col : block.col_view()) {
        std::cout << col << std::endl;
    }

    #if 0

    Matrix<double> weight(1, 2);

    Matrix<double> b(1, 1);

    reg::fill_random(weight);
    reg::fill_random(b);

    double cost = reg::MSE<double>(data, weight, b);

    std::cout << weight << std::endl;
    std::cout << b << std::endl;
    printf("Cost: %.6lf\n", cost);

    for (auto& single : data) {
        Matrix real = reg::forward(const Matrix<T> &params, const Matrix<T> &weight, const Matrix<T> &bais);
        sigmoid_mat(real);
        printf("%lf %lf : %lf\n", single[0], single[1], reg::forward(const Matrix<T> &params, const Matrix<T> &weight, const Matrix<T> &bais))
    }

    #endif

}
