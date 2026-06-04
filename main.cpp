#include "clustering.hpp"
#include "matrix.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 800

#define POINT_RADIUS 15

Vector2 matrix_to_raylib_Vector2(const mat::Matrix<double> &mat) {
    Vector2 result;
    result.x = mat.items[0] * 70 + WIDTH / 2;
    result.y = HEIGHT / 2 - mat.items[1] * 70;

    return result;
}

int main() {

    InitWindow(WIDTH, HEIGHT, "Hello Raylib!");

    mat::Matrix<double> data = {
        {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 3}, {4, 4}, {3, 4},
    };

    std::vector<Vector2> centroids;
    mat::Matrix<double> centers = clus::kmeans(data, 2, 100000);
    std::cout << centers;
    for (auto centroid : centers.row_view()) {
        centroids.push_back(matrix_to_raylib_Vector2(centroid));
    }

    while (!WindowShouldClose()) {

        ClearBackground(WHITE);
        std::vector<Vector2> points;

        for (auto point : data.row_view()) {
            points.push_back(matrix_to_raylib_Vector2(point));
        }

        BeginDrawing();
        for (auto point : points) {
            DrawCircleV(point, POINT_RADIUS, BLACK);
        }

        for (auto center : centroids) {
            DrawCircleV(center, POINT_RADIUS, RED);
        }

        EndDrawing();
    }
}
