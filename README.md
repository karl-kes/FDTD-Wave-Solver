# 3D Finite-Difference Time-Domain Electromagnetic Wave Simulator (WIP)
 
A high-performance Finite-Difference Time-Domain (FDTD) solver for Maxwell's equations in 3D, implemented in C++ with OpenMP parallelization and interactive Plotly visualization.

![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B)
![OpenMP](https://img.shields.io/badge/OpenMP-Parallel-green)
![Python](https://img.shields.io/badge/Python-3.x-yellow?logo=python)

## Overview

This project implements the **Yee algorithm** for solving Maxwell's curl equations on a staggered grid. The FDTD method discretizes both space and time, updating electric and magnetic fields in a leapfrog scheme that naturally satisfies Faraday's and Ampère's laws.

### Maxwell's Equations (Vacuum)

The solver implements the two curl equations:

$$\frac{\partial \mathbf{B}}{\partial t} = -\nabla \times \mathbf{E}$$

$$\frac{\partial \mathbf{E}}{\partial t} = c^2 \nabla \times \mathbf{B}$$

### CFL Stability Condition

The time step is automatically calculated to satisfy the Courant-Friedrichs-Lewy condition:

$$\Delta t <= \frac{1.0}{c \sqrt{\frac{1}{\Delta x^2} + \frac{1}{\Delta y^2} + \frac{1}{\Delta z^2}}}$$

## Quick Start

### Prerequisites

- C++17 compiler (GCC recommended)
- OpenMP support
- Python 3.x with NumPy, Pandas, and Plotly

### Build & Run

```bash
# Compile with OpenMP (recommended)
g++ -std=c++17 main.cpp -o main.exe -fopenmp
./main.exe
./render.py
```

### Without OpenMP

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
./render.py
```

### Grid Constructor Parameters

| Parameter | Description | Default |
|-----------|-------------|---------|
| `Nx, Ny, Nz` | Grid dimensions | 10 |
| `dx, dy, dz` | Spatial step sizes | 1.0 |
| `c` | Speed of light | 1.0 |

## Visualization

The included Python script generates an interactive 3D animation of field evolution:

```python
python render.py
```

## Project Structure

```
├── main.cpp          # Grid class and simulation driver
├── render.py      # Plotly animation generator
├── output/           # CSV slice exports
└── README.md
```

## Performance

*Results vary by hardware. The `collapse(2)` and `simd` pragmas optimize the nested loops for parallel execution.*