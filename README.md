# 2D Kinematics & Time Integration Simulator

A deterministic 2D kinematic simulator written in **C++ using Raylib**, designed to explore **numerical integration methods** commonly used in robotics, autonomous systems, and aerospace simulation.

The project allows **runtime comparison** between different integrators and includes a **stress mode** to visually highlight numerical stability differences.

---

## 🎯 Features

- Fixed-step simulation loop (deterministic)
- Semi-implicit Euler integrator
- Second-order Runge–Kutta (RK2 / Midpoint) integrator
- Runtime integrator switching
- Stress mode with increased timestep
- Acceleration-based inertial motion
- Trajectory trail visualization
- Clean separation between simulation and rendering

---

## 🎮 Controls

| Key | Action |
|---|---|
| **W A S D** | Apply acceleration |
| **1** | Switch to Euler integrator |
| **2** | Switch to RK2 integrator |
| **T** | Toggle Stress Mode |
| **R** | Reset simulation |
| **ESC** | Exit |

---

## 🔬 Integrators

### Euler (Semi-Implicit)
A first-order integration method that updates velocity before position.

- Very fast
- Simple to implement
- Accumulates numerical error more quickly
- Becomes unstable with larger timesteps

### RK2 (Midpoint)
A second-order Runge–Kutta method that evaluates system behavior at the midpoint of the timestep.

- Improved numerical accuracy
- Better stability under stress
- Reduced error accumulation
- Still computationally inexpensive

---

## ⚠️ Stress Mode

Stress Mode intentionally increases the simulation timestep to make numerical errors visible.

- **Normal Mode**: 100 Hz timestep  
- **Stress Mode**: 25 Hz timestep  

Under stress conditions:
- Euler exhibits visible drift and instability
- RK2 maintains smoother and more stable trajectories

This mode exists purely to demonstrate numerical behavior differences.

---

## 🧠 Architecture


The simulation logic is fully decoupled from rendering, making the system suitable for:
- Headless simulation
- Offline analysis
- Monte Carlo experiments
- Future control and dynamics extensions

---

## 🔧 Build & Run (Linux)

### Dependencies
- g++
- Raylib

### Build
```bash
g++ -Isrc $(find src -name '*.cpp') -o app -std=c++17 \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
### Run
./app

## 🚀 Motivation

This project serves as a foundation for further exploration into:

- Numerical integration methods
- Autonomous navigation
- Guidance, Navigation & Control (GNC)
- Robotics and aerospace simulation
- Control systems (PID, tracking)
- Physics-based dynamics