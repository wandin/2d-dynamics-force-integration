#include "Integrator.hpp"

// Dispatcher
void Integrator::Step(State &State, float DeltaTime, IntegratorType Type)
{
    switch(Type)
    {
        case IntegratorType::Euler:
        Euler(State, DeltaTime);
        break;
        
        case IntegratorType::RK2:
        RK2(State, DeltaTime);
        break;
    }
}

// Semi implicit Euler
void Integrator::Euler(State &State, float DeltaTime)
{
    State.Velocity.x += State.Acceleration.x * DeltaTime;
    State.Velocity.y += State.Acceleration.y * DeltaTime;

    State.Position.x += State.Velocity.x * DeltaTime;
    State.Position.y += State.Velocity.y * DeltaTime;
}

// RK2 Midpoint
void Integrator::RK2(State &State, float DeltaTime)
{
    // State at midpoint
    Vector2 MidVelocity = {
        State.Velocity.x + State.Acceleration.x * (DeltaTime * 0.5f),
        State.Velocity.y + State.Acceleration.y * (DeltaTime * 0.5f)
    };

    // --- integrate full step
    State.Position.x += MidVelocity.x * DeltaTime;
    State.Position.y += MidVelocity.y * DeltaTime;

    State.Velocity.x += State.Acceleration.x * DeltaTime;
    State.Velocity.y += State.Acceleration.y * DeltaTime;
}
