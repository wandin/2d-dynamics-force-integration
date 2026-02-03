#include <raylib.h>
#include <raymath.h>
#include "render/Renderer.hpp"
#include "simulation/State.hpp"
#include "simulation/Integrator.hpp"
#include "simulation/Dynamics.hpp"

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D Kinematics & Time Integration");
    SetTargetFPS(120);
    ToggleFullscreen();

    constexpr float FixedDeltaTime = 1.0f / 100.0f; // 100 Hz
    float accumulator = 0.0f;

    double lastTime = GetTime();

    State state;
    state.Position = { WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f };

    IntegratorType CurrentIntegrator = IntegratorType::Euler;
    
    // Stress mode toggle
    bool StressMode = false;

    while (!WindowShouldClose())
    {
        double currentTime = GetTime();
        float frameTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        constexpr float MaxFrameTime = 0.25f;
        if (frameTime > MaxFrameTime)
        {
            frameTime = MaxFrameTime;
        }

        accumulator += frameTime;

        Vector2 inputDir = {0.0f, 0.0f};

        if (IsKeyPressed(KEY_ONE))
        {
            CurrentIntegrator = IntegratorType::Euler;
        }

        if (IsKeyPressed(KEY_TWO))
        {
            CurrentIntegrator = IntegratorType::RK2;
        }

        if (IsKeyDown(KEY_W)) inputDir.y -= 1.0f;
        if (IsKeyDown(KEY_S)) inputDir.y += 1.0f;
        if (IsKeyDown(KEY_A)) inputDir.x -= 1.0f;
        if (IsKeyDown(KEY_D)) inputDir.x += 1.0f;
        if (IsKeyPressed(KEY_DOWN))
        {
            state.Mass = std::max(0.1f, state.Mass - 0.2f);
        }
        if (IsKeyPressed(KEY_UP))
        {
            state.Mass += 0.2f;
        }   

        if(IsKeyDown(KEY_R))
         {
            //Stop movement
            state.Force = {0.0f, 0.0f};
            state.Velocity = {0.0f, 0.0f};
            state.Acceleration = {0.0f, 0.0f};
            //Center object
            state.Position.x = WINDOW_WIDTH * 0.5f;
            state.Position.y = WINDOW_HEIGHT * 0.5f;
            //Clearing trail
            state.Trail.clear();
        }
        
        // Stress mode
        if (IsKeyPressed(KEY_T))
        {
            StressMode = !StressMode;
        }

        if (Vector2Length(inputDir) > 0.0f)
        {
            inputDir = Vector2Normalize(inputDir);
        }

        float simulationDt = StressMode ? (1.0f / 25.0f) : FixedDeltaTime;

        constexpr float InputForce = 800.0f;
        state.Force = Vector2Scale(inputDir, InputForce);

        while (accumulator >= simulationDt)
        {
            Dynamics::ComputeAcceleration(state, /*DragEnabled=*/true);
            Integrator::Step(state, simulationDt, CurrentIntegrator);
            accumulator -= simulationDt;
        }

        state.Trail.push_back(state.Position);
        if (state.Trail.size() > 1000)
        {
            state.Trail.erase(state.Trail.begin());
        }

        Renderer::Draw(state, CurrentIntegrator, StressMode, simulationDt);
    }

    CloseWindow();
    return 0;
}
