#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <vector>

namespace clus {

struct Cluster {
    mat::Matrix<double> centroid;
    std::vector<mat::Matrix<double>> points;

    Cluster() = default;
    Cluster(const mat::Matrix<double> &centroid) : centroid(centroid) {}
};

template <typename T> std::vector<Cluster> kmeans(mat::Matrix<T> &data, size_t k) {
    std::vector<Cluster> clusters(k, Cluster((3, func::randmat(1, data.cols, 0, 10))));

    for (auto point : data.row_view()) {
        double min = 1000000.f;
        for (auto cluster : clusters) {
            double dist = func::dist(cluster.centroid, point);
            min = min < dist ? min : dist;
        }
    }
    return clusters;
}
} // namespace clus

#endif // CLUSTERTING_HPP_
