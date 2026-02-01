#pragma once

#include <raylib.h>
#include "simulation/State.hpp"
#include "simulation/Integrator.hpp"

class Renderer
{
public:
    static void Draw(const State& State, IntegratorType Type, bool StressMode, float SimulationDt);
};