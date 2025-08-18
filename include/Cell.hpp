#pragma once

#include <SFML/Graphics.hpp>

class Cell {
    bool alive_;
    sf::Color color_alive_;
    sf::Color color_dead_;

public:
    Cell();
    Cell(bool alive, sf::Color color_alive, sf::Color color_dead);

    void Toggle();
    bool IsAlive() const { return alive_; }
    sf::Color GetColorAlive() const { return color_alive_; }
    sf::Color GetColorDead() const { return color_dead_; }
};