#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
namespace clus {
    template<typename T>
    mat::Matrix<T> kmeans(mat::Matrix<T> &data, size_t k) {
        std::vector<mat::Matrix<T>> centroids(k);
        for (auto centroid : centroids) {
            centroid = data.row_view()[size_t(func::randf(0, data.rows))];
        }

    }
}

#endif // CLUSTERTING_HPP_
