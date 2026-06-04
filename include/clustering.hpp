#ifndef CLUSTERTING_HPP_
#define CLUSTERTING_HPP_

#include "functions.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <limits>
#include <vector>

namespace clus {

struct Point {
    size_t id;
    mat::Matrix<double> point;
    size_t cluster_id;

    Point() = default;

    Point(size_t _id, mat::Matrix<double> &_point, size_t _cluster_id)
        : id(_id), point(_point), cluster_id(_cluster_id) {}
};

struct Cluster {
    size_t id;
    mat::Matrix<double> centroid;
    std::vector<Point *> points;

    Cluster() = default;

    Cluster(size_t _id, const mat::Matrix<double> &_centroid) : id(_id), centroid(_centroid) {}
};

mat::Matrix<double> kmeans(mat::Matrix<double> &data, size_t k, size_t iter) {
    std::vector<Cluster> clusters;
    for (size_t i = 0; i < k; ++i)
        clusters.push_back(Cluster(i, func::randmat(1, data.cols, 0, 5)));

    std::vector<Point *> points;
    for (size_t i = 0; i < data.rows; ++i) {
        mat::Matrix<double> point = data.row_view()[i];
        points.push_back(new Point(i, point, 0));
    }

    while (iter--) {
        for (size_t i = 0; i < points.size(); ++i) {
            double min = std::numeric_limits<double>::max();
            for (size_t j = 0; j < clusters.size(); ++j) {
                double d = func::dist(points[i]->point, clusters[j].centroid);
                if (d < min) {
                    min = d;
                    points[i]->cluster_id = j;
                }
            }
        }

        for (size_t i = 0; i < clusters.size(); ++i) {
            clusters[i].points.clear();
            for (auto point : points) {
                if (point->cluster_id == i)
                    clusters[i].points.push_back(point);
            }
        }

        for (size_t i = 0; i < clusters.size(); ++i) {
            if (clusters[i].points.empty())
                continue;
            mat::Matrix<double> new_center(1, data.cols);
            for (auto point : clusters[i].points)
                new_center += point->point;
            new_center /= (double)clusters[i].points.size();
            clusters[i].centroid = new_center;
        }
    }

    mat::Matrix<double> result(k, data.cols);
    for (size_t i = 0; i < k; ++i)
        result.row_view()[i] = clusters[i].centroid;

    for (auto p : points)
        delete p;

    return result;
}

} // namespace clus

#endif // CLUSTERTING_HPP_
