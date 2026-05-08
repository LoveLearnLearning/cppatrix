#include "graph.hpp"
#include "raylib.h"

void graph::DrawAxis(float width, float height, float edge, float thick, Color color) {
    Vector2 center = {width / 2, height / 2};

    Vector2 asp = {edge, center.y};
    Vector2 aep = {width - edge, center.y};
    Vector2 asv = {center.x, edge};
    Vector2 aev = {center.x, height - edge};

    DrawLineEx(asp, aep, thick, color);
    DrawLineEx(asv, aev, thick, color);

}
