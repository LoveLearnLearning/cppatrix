#include "raylib.h"
#include "raymath.h"
#include <vector>

#define WIDTH 640
#define HEIGHT 320

#define POINT_RADIUS 20

int main() {

    InitWindow(WIDTH, HEIGHT, "Hello Raylib!");

    while (!WindowShouldClose()) {

        ClearBackground(GRAY);
        std::vector<Vector2> points;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            points.push_back(GetMousePosition());
        }

        BeginDrawing();
        for (auto point : points) {
            DrawCircleV(point, POINT_RADIUS, RED);
        }

        EndDrawing();
    }

    CloseWindow();
}
