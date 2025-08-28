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
    - Numkeys to switch entity spawn type:
        - Num1: Humans (Blue)
        - Num2: Wolves (Red)
        - Num3: Plants (Green)
        - Num4: Walls (Brown-Gray)
    - Left-click to spawn entities, right-click to empty the cell.
    - Spacebar to start/stop simulation.
    - Right arrow to step forward.

### Behavior
Each fraction has predefined stats and behaviors. For now:
- Humans:
    - hp, damage, and hunger. Right now hunger is useless, but will be built upon.
    - Humans will fight off wolves, and feed off of the dead ones or plants.
    - Repopulate as in the default Game of Life. Will be changed later.
- Wolves:
    - hp, damage, and hunger. Again, hunger is useless as of now.
    - Wolves will hunt surrounding humans and feed off of them. They hit a lot harder than humans. If no humans found, they will eat plants.
    - Repopulation logic is also the same.
- Plants:
    - Plants don't die out due to overpopulation.
    - They spawn with low hp, but heal off over time.
    - Plants with more than half hp attack surrounding walls, eventually occupying their place.
- Walls:
    - Do not auto-spawn or destruct.
    - Can only be attacked by plants.
    - Block other entities' movement.

## Notes
All required assets and DLLs are copied automatically by CMake.
If you move the executable, also copy the assets folder and SFML DLLs.
