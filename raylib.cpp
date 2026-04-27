#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "Hello Raylib!");

    while (!WindowShouldClose()) {
    BeginDrawing();
        ClearBackground(RED);
        DrawText("Hello Raylib", 400, 300, 20, BLACK);
    EndDrawing();
    }

    CloseWindow();

    return 0;


}
