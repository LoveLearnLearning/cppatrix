#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "raylib.h"


namespace graph {
    void DrawAxis(float width, float height, float edge = 100, float thick = 5, Color color = BLACK);

    template<typename Function>
    void DrawFunction(float width, float height, float x_s, float x_e, Function func, float thick = 2, Color color = BLACK) {
        Vector2 center = {width / 2, height / 2};

        for (float x = x_s; x <= x_e; x += 0.01) {
            float y = func(x);
            DrawCircleV(Vector2 {center.x + x, center.y - y}, thick, color);
        }
    }
}





#endif // GRAPH_HPP_
