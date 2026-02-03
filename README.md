# 2D Dynamics – Force, Mass & Numerical Integration

A deterministic **2D dynamics simulator** written in **C++ using Raylib**, focused on modeling **force-based motion**, **mass effects**, and **numerical integration stability**.

This project extends a previous kinematics-only simulator into a **Newtonian dynamics model**, making acceleration an emergent property derived from forces rather than a direct input. It also provides real-time visual feedback to compare different integration methods under stress.

---

## 🎯 Project Goals

- Model **force → acceleration → velocity → position** correctly
- Compare numerical integration methods (Euler vs RK2)
- Visualize physical quantities (force, acceleration, energy)
- Expose numerical instability using controlled timestep stress
- Keep a clean, modular simulation architecture

This project is designed as a learning and demonstration tool for **physics simulation**, **robotics**, and **aerospace/GNC fundamentals**.

---

## 🧱 Architecture Overview

The simulator is intentionally split into clear, independent modules:

- State → Physical state (data only)
- Dynamics → Force resolution (physics laws)
- Integrator → Numerical integration
- Renderer → Visualization & HUD
- Main Loop → Orchestration & input


### Key Design Principle

> **The integrator never computes forces.**  
> **The dynamics module never updates position.**

This separation mirrors real-world simulation and control software.

---

## ⚙️ Physical Model

- **Input** applies a force vector
- **Acceleration** is computed using Newton’s second law: 
```
a = F / m
 ```

- **Linear drag** is applied as a resistive force:
```
F_drag = -k · v
 ```

- Motion exhibits inertia, damping, and mass-dependent response

---

## 🔬 Numerical Integrators

### Euler (Semi-Implicit)
- First-order method
- Very fast and simple
- Accumulates numerical error quickly
- Becomes unstable with larger timesteps

### RK2 (Midpoint)
- Second-order Runge–Kutta method
- Evaluates system state at the midpoint of the timestep
- Improved stability and energy behavior
- Still computationally inexpensive

Integrators can be switched **at runtime**.

---

## ⚠️ Stress Mode

Stress Mode intentionally increases the simulation timestep to highlight numerical instability.

| Mode | Simulation Timestep |
|----|----|
| Normal | 100 Hz |
| Stress | 25 Hz |

Under stress conditions:
- Euler shows drift, overshoot, and energy gain
- RK2 maintains smoother and more stable motion

This mode exists purely to **make numerical behavior visible**.

---

## 🎨 Visual Feedback

The simulator uses multiple visual cues to communicate physical behavior:

### Vectors
- **Yellow vector** → Applied force (input)
- **Red vector** → Resulting acceleration

### Trajectory Trail
Trail color changes depending on motion regime:
- **Green** → Active acceleration
- **Blue** → Inertial coasting
- **Red** → Braking / drag-dominated motion

### HUD
- Position and velocity
- Current integrator
- Timestep and stress mode
- Mass value
- Kinetic energy
- FPS

These visuals allow the system’s physics to be understood **without reading code**.

---

## 🎮 Controls

| Key | Action |
|---|---|
| **W A S D** | Apply force |
| **↑ / ↓** | Increase / decrease mass |
| **1** | Switch to Euler integrator |
| **2** | Switch to RK2 integrator |
| **T** | Toggle Stress Mode |
| **R** | Reset simulation |
| **ESC** | Exit |

---

## 🛠️ Build & Run

### Requirements
- Linux
- C++17 compiler (g++ or clang)
- Raylib

### Build (example)
```bash
mkdir -p build
g++ -Isrc $(find src -name '*.cpp') -o build/app \
  -std=c++17 -Wall -Wextra \
  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Run
```bash
./build/app
```

### 📚 Background & Motivation

- This project is part of a progressive simulation series:
- 2D Kinematics – Position, velocity, time integration
- 2D Dynamics (this project) – Force, mass, drag
- Orbital Motion & Energy Preservation (planned)
- Control Systems & Estimation (planned)
- The focus is not visual fidelity, but numerical correctness, clarity, and engineering structure.

### 📜 License

This project is provided for educational and demonstration purposes.