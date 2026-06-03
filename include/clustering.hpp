#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>

namespace clus {

struct Point {
    int id;
    mat::Matrix<double> point;
    int cluster_id;

    Point() = default;

    Point(int _id, mat::Matrix<double> &_point, int _cluster_id)
        : id(_id), point(_point), cluster_id(_cluster_id) {}
};

struct Cluster {
    int id;
    mat::Matrix<double> centroid;
    std::vector<mat::Matrix<double> *> points;

    Cluster() = default;

    Cluster(const mat::Matrix<double> &centroid) : centroid(centroid) {}

    Cluster(int _id, const mat::Matrix<double> &_centroid,
            std::vector<mat::Matrix<double> *> _points)
        : id(_id), centroid(_centroid), points(_points) {}
};

template <typename T> std::vector<Cluster> kmeans(mat::Matrix<T> &data, size_t k) {

    std::vector<Cluster> clusters;
    for (size_t i = 0; i < k; ++i) {
        clusters.push_back(Cluster(i, func::randmat(1, data.cols, 0, 10), nullptr));
    }

    std::vector<Point *> points;
    for (size_t i = 0; i < data.rows; ++i) {
        mat::Matrix<double> point = data.row_view()[i];
        points.push_back(new Point(i, point, 0));
    }

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < clusters.size(); ++i) {
            double dist = func::dist(points[i]->point, clusters[i].centroid);
        }
    }

    return clusters;
}
} // namespace clus

#endif // CLUSTERTING_HPP_
