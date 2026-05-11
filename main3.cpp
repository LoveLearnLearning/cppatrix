#include "graph.hpp"
#include "matrix.hpp"
#include "functions.hpp"
#include "regression.hpp"
#include "raylib.h"

#include <cstddef>
#include <cstdlib>
#include <print>


int main() {

    mat::Matrix<double> train = {
        {1, 2},
        {2, 4},
        {3, 6},
        {4, 8},
        {5, 10},
    };

    double w = func::randf(1, 10);

    std::println("WeightBefore: {}", w);
    std::println("Cost: {}", reg::MSE(train, w));

    float width  = 800;
    float height = 600;

    InitWindow(width, height, "Machine Learning");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            graph::DrawAxis(width, height);
            graph::DrawFunction(width, height, -100, 100, [&](double x) {
                return 0.005 * reg::MSE(train, x);
            });

            for (size_t i = 0; i < 100; ++i) {
                w = reg::dMSE(train, w, 1e-3);
                std::println("Cost: {}", reg::MSE(train, w));
            }

            for (auto row : train.row_view()) {
                std::println("{} -> {} : {}", row(0, 0), reg::forward(row, w), row(0, 1));
            }

            std::println("WeightAfter: {}", w);
            std::println("Cost: {}", reg::MSE(train, w));
        EndDrawing();

    }



}
