#pragma once

#include "raylib.h"
#include <vector>

struct State
{
    Vector2 Position{0.0f, 0.0f};
    Vector2 Velocity{0.0f, 0.0f};
    Vector2 Acceleration{0.0f, 0.0f};

    std::vector<Vector2> Trail;
};