# 2D Raytracing Simulation

A simple real-time 2D raytracing simulation built with C++ and SFML.    

This branch has continuous lighting in the form of a polygon
![til](https://github.com/shujaK/2D-RayCasting/blob/smooth-shadows/smooth_demo.gif)     


Inspired by: https://ncase.me/sight-and-light/
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