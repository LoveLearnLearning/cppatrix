#include "clustering.hpp"
#include "matrix.hpp"
#include <iostream>

int main() {
    mat::Matrix<double> data = {
        {1, 2}, {2, 2}, {1, 3}, {2, 4}, {3, 3}, {4, 3}, {4, 4},
    };

    mat::Matrix<double> new_centroid = clus::kmeans(data, 2);

    std::cout << new_centroid << std::endl;

    mat::Matrix<double> vec1 = {
        {1, 3, 2, 1, 2, 1, 1},
    };
    mat::Matrix<double> vec2 = {
        {7, 0, 2, 1, 0, 0, 1},
    };

    mat::Matrix<double> vec3 = {
        {1, 7, 0, 0, 2, 0, 1},
    };
    mat::Matrix<double> vec4 = {
        {1, 0, 0, 0, 7, 1, 2},
    };
    mat::Matrix<double> vec5 = {
        {0, 2, 0, 0, 7, 1, 1},
    };

    std::cout << "1: " << vec1 * vec2.transpose() << std::endl;
    std::cout << "2: " << vec1 * vec3.transpose() << std::endl;
    std::cout << "3: " << vec1 * vec4.transpose() << std::endl;
    std::cout << "4: " << vec1 * vec5.transpose() << std::endl;
}
