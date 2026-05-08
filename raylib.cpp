#include "raylib.h"
#include "graph.hpp"

int main(void) {
    float width  = 800;
    float height = 600;

    InitWindow(width, height, "Hello Raylib!");

    while (!WindowShouldClose()) {
    BeginDrawing();
        ClearBackground(WHITE);

        graph::DrawAxis(width, height);

        graph::DrawFunction(width, height, -100, 100, [](float x) -> float {
            return 0.05 * x * x;
        });

        float ptx = 20;
        float pty = 0.05 * ptx * ptx;
        float k  = 0.1 * ptx;
        float b  = pty - k * ptx;

        graph::DrawFunction(width, height, -100, 100, [&](float x) {
            return k * x + b;
        });


    EndDrawing();
    }

    CloseWindow();

    return 0;


}
