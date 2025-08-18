#include "GameOfLife.hpp"

int main()
{
    const unsigned int kWindowWidth = 1280;
    const unsigned int kWindowHeight = 720;
    const unsigned int kCellSize = 20;
    const float kTickRate = 0.2f;

    GameOfLife game(kWindowWidth, kWindowHeight, kCellSize, kTickRate);
    game.Run();

    return 0;
}