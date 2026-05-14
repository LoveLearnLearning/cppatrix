#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
namespace clus {
template <typename T> mat::Matrix<T> kmeans(mat::Matrix<T> &data, size_t k) {
    std::vector<mat::Matrix<T>> centroids(k);
    std::vector<std::pair<mat::Matrix<T>, mat::Matrix<T>>> crowds(data.rows);
    mat::Matrix<T> result(k, data.cols);
    for (size_t i = 0; i < k; ++i) {
        centroids[i] = data.row_view()[(size_t)func::randf(0, data.rows)];
        std::cout << centroids[i] << std::endl;
    }
    for (size_t i = 0; i < data.rows; ++i) {
        double min = 100000.f;
        for (auto centroid : centroids) {
            double dist = func::dist(static_cast<mat::Matrix<T>>(data.row_view()[i]), centroid);
            if (dist < min) {
                min = dist;
                crowds[i] = {data.row_view()[i], centroid};
            }
        }
    }
    for (size_t i = 0; i < centroids.size(); ++i) {
        mat::Matrix<T> new_centroid(1, data.cols);
        size_t count = 0;
        for (auto crowd : crowds) {
            if (crowd.second == centroids[i]) {
                new_centroid += crowd.first;
                count++;
                std::cout << new_centroid << std::endl;
            }
        }
        result.row_view()[i] = count == 0 ? result.row_view()[i] : new_centroid * (1 / count);
    }
    return result;
}

} // namespace clus

#endif // CLUSTERTING_HPP_
