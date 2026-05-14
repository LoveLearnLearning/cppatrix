#include "clustering.hpp"
#include "matrix.hpp"
#include <iostream>

int main() {
    mat::Matrix<double> data = {
        {1, 2}, {2, 2}, {1, 3}, {2, 4}, {3, 3}, {4, 3}, {4, 4},
    };

    mat::Matrix<double> new_centroid = clus::kmeans(data, 2);

    std::cout << new_centroid << std::endl;
}
