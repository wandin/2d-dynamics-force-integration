#pragma once

#include "simulation/State.hpp"

class Dynamics
{
public:
    static void ComputeAcceleration(State& State, bool DragEnabled);
};  