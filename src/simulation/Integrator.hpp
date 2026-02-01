#pragma once

#include "simulation/State.hpp"

enum class IntegratorType
{
    Euler = 0,
    RK2
};

class Integrator
{
public:

    static void Step(State& State, float DeltaTime, IntegratorType Type);

private:

    static void Euler(State& State, float DeltaTime);
    static void RK2(State& State, float DeltaTime);
};