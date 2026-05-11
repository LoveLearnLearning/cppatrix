#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <utility>
#include <vector>
namespace clus {
    template<typename T>
    mat::Matrix<T> kmeans(mat::Matrix<T> &data, size_t k) {
        std::vector<mat::Matrix<T>> centroids(k);
        std::vector<std::pair<mat::Matrix<T>, mat::Matrix<T>>> crowds(data.rows);
        for (auto centroid : centroids) {
            centroid = data.row_view()[size_t(func::randf(0, data.rows))];
        }
        for (size_t i = 0; i < data.rows; ++i) {
            double min = 100000.f;
            for (auto centroid : centroids) {
                double dist = func::dist(data.row_view()[i], centroid);
                if (dist < min) {
                    min = dist;
                    crowds[i] = {data.row_view()[i], centroid};
                }
            }
        }
    }
}

#endif // CLUSTERTING_HPP_
