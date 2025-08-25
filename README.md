# 2D Raytracing Simulation

A simple real-time 2D raytracing simulation built with C++ and SFML. 
This branch has continuous lighting in the form of a polygon
![til](https://raw.githubusercontent.com/shujaK/2D-RayCasting/refs/heads/main/demo.gif)
## Features

- Move the mouse to control the light source position
- Click and drag to create walls that block light rays

## Controls

- **Mouse Movement**: Controls the position of the light source (eye)
- **Left Click + Drag**: Creates new walls by drawing from start to end point
- **D Key**: Clears all walls from the scene

## Building

Requires CMake and SFML. Build with:
```bash
mkdir build
cd build
cmake ..
make
```