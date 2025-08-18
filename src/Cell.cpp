#include <SFML/Graphics.hpp>
#include <Cell.hpp>

Cell::Cell() : alive_(false), color_alive_(sf::Color(200, 200, 200)), color_dead_(sf::Color::White) {}
Cell::Cell(bool alive, sf::Color color_alive, sf::Color color_dead)
    : alive_(alive),
      color_alive_(color_alive),
      color_dead_(color_dead) {}

void Cell::Toggle() {
    alive_ = !alive_;
}