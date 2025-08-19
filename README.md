# Game of Life++
A C++ implementation of Conway’s Game of Life with a graphical interface (SFML 3.0).
This project is designed for learning and experimenting with modern C++.

## Setup Instructions
### Prerequisites
- C++20 compatible compiler (MSVC, GCC, or Clang)
- SFML 3.0
- CMake 3.16 or newer

## Building
1. Clone the repository:
```bash
git clone https://github.com/Allexsen/GoL-PlusPlus
cd GoL-PlusPlus
```
2. Make sure SFML-3.0.0 is present (or update CMakeLists.txt to your SFML path).
3. Run CMake to configure and build:
```bash
cmake -S . -B build
cmake --build build
```
4. The executable will be in Debug (or build/Release).

## Running
Run the executable:
```bash
./build/Debug/game_of_life.exe
```
- The window will open.
    - Left-click to toggle cells.
    - Spacebar to start/stop simulation.
    - Right arrow to step forward.

## Notes
All required assets and DLLs are copied automatically by CMake.
If you move the executable, also copy the assets folder and SFML DLLs.
