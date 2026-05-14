#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <utility>
#include <vector>
namespace clus {
template <typename T> mat::Matrix<T> kmeans(mat::Matrix<T> &data, size_t k) {
    std::vector<mat::Matrix<T>> centroids(k);
    std::vector<std::pair<mat::Matrix<T>, mat::Matrix<T>>> crowds(data.rows);
    mat::Matrix<T> result(k, data.cols);
    for (mat::Matrix<T> centroid : centroids) {
        centroid = data.row_view()[1];
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
    for (size_t i = 0; i < centroids.size(); ++i) {
        mat::Matrix<T> new_centroid(1, data.cols);
        size_t count = 0;
        for (auto crowd : crowds) {
            if (crowd.second == centroids[i]) {
                new_centroid += crowd.first;
                count++;
            }
        }
        result.row_view()[i] = count == 0 ? result.row_view()[i] : new_centroid / count;
    }
    return result;
}

} // namespace clus

#endif // CLUSTERTING_HPP_
