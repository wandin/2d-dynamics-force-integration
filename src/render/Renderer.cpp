#include "Renderer.hpp"
#include <raymath.h>

void Renderer::Draw(const State& State, IntegratorType Type, bool StressMode, float SimulationDt)
{
    BeginDrawing();

    ClearBackground(BLACK);

    Color trailColor = GREEN;

    // Drawing trail before the circule...pure cosmetic
    for (size_t i = 1; i < State.Trail.size(); ++i)
    {

        if (Vector2Length(State.Acceleration) < 1.0f && Vector2Length(State.Velocity) > 10.0f)
        {
            trailColor = SKYBLUE; // Inertial coast
        }
        else if (Vector2DotProduct(State.Acceleration, State.Velocity) < 0.0f)
        {
            trailColor = RED; // Braking (drag)
        }

        //DrawLineV(State.Trail[i-1], State.Trail[i], DARKGRAY);
        DrawLineBezier(State.Trail[i-1], State.Trail[i], 2, trailColor);
    }

    DrawCircleV(State.Position, 10.0f, RED);
    DrawCircleLines(State.Position.x, State.Position.y, 10.0f, WHITE);


    const char* integratorName = (Type == IntegratorType::Euler) ? "Euler (Semi-Implicit)" : "RK2 (Midpoint)";

    DrawText(TextFormat("Integrator: %s", integratorName), 10, 130, 20, DARKBLUE);

    DrawText(TextFormat("Timestep: %.2f %s", SimulationDt,
        StressMode ? "(Stress Mode)" : ""), 10, 190, 20, StressMode ? RED : DARKGREEN);

    DrawText("Press [T] Toggle Stress Mode", 10, 220, 20, GRAY);

    DrawText("Press [1] Euler | [2] RK2 | [R] Reset", 10, 160, 20, GRAY);

    DrawText(TextFormat("Position: (x: %.2f, y: %.2f)",
                        State.Position.x, State.Position.y), 10, 40, 20, DARKGRAY);

    DrawText(TextFormat("Velocity: (x: %.2f, y: %.2f)",
                        State.Velocity.x, State.Velocity.y), 10, 70, 20, DARKGRAY);

        DrawText(TextFormat("Mass: %.2f", State.Mass),
                            10, 250, 20, State.Mass > 2.0f ? ORANGE : DARKGREEN);

        Vector2 forceVec = Vector2Scale(State.Force, 0.05f);
            DrawLineV(State.Position,
            Vector2Add(State.Position, forceVec),
          YELLOW);

        Vector2 accelVec = Vector2Scale(State.Acceleration, 0.05f);
            DrawLineV(State.Position, Vector2Add(State.Position, accelVec), RED);

        float kineticEnergy = 0.5f * State.Mass * Vector2LengthSqr(State.Velocity);

        DrawText(TextFormat("Kinetic Energy: %.1f", kineticEnergy),
                10, 330, 18,
                StressMode ? RED : LIGHTGRAY);

        DrawText("Yellow: Force", 10, 280, 18, YELLOW);
        DrawText("Red: Acceleration", 10, 300, 18, RED);


    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 100, 20, DARKGRAY);

    EndDrawing();
}