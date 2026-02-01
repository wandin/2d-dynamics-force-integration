#include "Renderer.hpp"

void Renderer::Draw(const State& State, IntegratorType Type, bool StressMode, float SimulationDt)
{
    BeginDrawing();

    ClearBackground(BLACK);

    // Drawing trail before the circule...pure cosmetic
    for (size_t i = 1; i < State.Trail.size(); ++i)
    {
        //DrawLineV(State.Trail[i-1], State.Trail[i], DARKGRAY);
        DrawLineBezier(State.Trail[i-1], State.Trail[i], 2, GREEN);
    }

    DrawCircleV(State.Position, 10.0f, RED);
    DrawCircleLines(State.Position.x, State.Position.y, 10.0f, WHITE);


    const char* integratorName = (Type == IntegratorType::Euler) ? "Euler (Semi-Implicit)" : "RK2 (Midpoint)";

    DrawText(TextFormat("Integrator: %s", integratorName), 10, 130, 20, DARKBLUE);

    DrawText(TextFormat("Timestep: %.2f %s", SimulationDt,
        StressMode ? "(Stress Mode)" : ""),
        10, 190, 20, StressMode ? RED : DARKGREEN);

    DrawText("Press [T] Toggle Stress Mode", 10, 220, 20, GRAY);

    DrawText("Press [1] Euler | [2] RK2 | [R] Reset", 10, 160, 20, GRAY);

    DrawText(TextFormat("Position: (x: %.2f, y: %.2f)",
        State.Position.x, State.Position.y),
        10, 40, 20, DARKGRAY);

    DrawText(TextFormat("Velocity: (x: %.2f, y: %.2f)",
        State.Velocity.x, State.Velocity.y),
        10, 70, 20, DARKGRAY);

    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 100, 20, DARKGRAY);

    EndDrawing();
}