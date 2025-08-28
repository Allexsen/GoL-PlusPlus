#include <SFML/Graphics.hpp>
#include "GameOfLife.hpp"
#include "Grid.hpp"
#include "EntityFactory.hpp"

GameOfLife::GameOfLife(unsigned int window_width, unsigned int window_height, unsigned int cell_size, float tick_rate)
    : window_(sf::VideoMode({window_width, window_height}), "Game of Life++"),
        window_width_(window_width),
        window_height_(window_height),
        cell_size_(cell_size),
        tick_rate_(tick_rate),
        accumulator_(0.0f),
        grid_(window_width, window_height, cell_size),
        running_(false) {
    window_.setFramerateLimit(60);
}

void GameOfLife::Run() {
    while (window_.isOpen()) {
        ProcessEvents();
        Update();
        Render();
    }
}

void GameOfLife::ProcessEvents() {
    while (const std::optional<sf::Event> event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window_.close();

        if (event->is<sf::Event::KeyPressed>()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                running_ = !running_;
                accumulator_ = tick_rate_;
                clock_.restart();
            }
            

            if (!running_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                grid_.Update();
        }

        if (!running_ && event->is<sf::Event::MouseButtonPressed>()) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
            int cell_x = mouse_pos.x / cell_size_;
            int cell_y = mouse_pos.y / cell_size_;

            if (cell_x >= 0 && cell_x < grid_.GetWidth() && cell_y >= 0 && cell_y < grid_.GetHeight()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    switch (spawn_type_) {
                        case EntityType::kHuman:
                            grid_.UpdateCell(cell_y, cell_x, EntityFactory::CreateHuman());
                            break;
                        case EntityType::kWolf:
                            grid_.UpdateCell(cell_y, cell_x, EntityFactory::CreateWolf());
                            break;
                        case EntityType::kPlant:
                            grid_.UpdateCell(cell_y, cell_x, EntityFactory::CreatePlant());
                            break;
                        case EntityType::kWall:
                            grid_.UpdateCell(cell_y, cell_x, EntityFactory::CreateWall());
                            break;
                    }
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                    grid_.EmptyCell(cell_y, cell_x);
                }
            }
        }

        // numeric keys switch spawn type
        if (!running_ && event->is<sf::Event::KeyPressed>()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) spawn_type_ = EntityType::kHuman;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) spawn_type_ = EntityType::kWolf;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) spawn_type_ = EntityType::kPlant;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) spawn_type_ = EntityType::kWall;
        }
    }
}

void GameOfLife::Update() {
    accumulator_ += clock_.restart().asSeconds();

    if (running_)
        while (accumulator_ >= tick_rate_) {
            grid_.Update();
            accumulator_ -= tick_rate_;
        }
}

void GameOfLife::Render() {
    window_.clear();
    grid_.Render(window_);
    window_.display();
}