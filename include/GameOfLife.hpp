#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Entity.hpp"

class GameOfLife {
public:
    GameOfLife(unsigned int window_width, unsigned int window_height, unsigned int cell_size, float tick_rate);
    void Run();
    void ProcessEvents();
    void Update();
    void Render();

private:
    unsigned int window_width_;
    unsigned int window_height_;
    unsigned int cell_size_;

    sf::RenderWindow window_;
    Grid grid_;
    sf::Clock clock_;

    bool running_;
    float tick_rate_;
    float accumulator_;
    EntityType spawn_type_ = EntityType::kHuman;
};