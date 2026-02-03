#include "Dynamics.hpp"
#include <raymath.h>

void Dynamics::ComputeAcceleration(State &State, bool DragEnabled)
{
    Vector2 DragForce{0.0f, 0.0f};

    if(DragEnabled)
    {
        constexpr float DragCoefficient = 0.8f;
        DragForce = Vector2Scale(State.Velocity, - DragCoefficient);
    }

    Vector2 TotalForce = Vector2Add(State.Force, DragForce);
    State.Acceleration = Vector2Scale(TotalForce, 1.0f / State.Mass);
}