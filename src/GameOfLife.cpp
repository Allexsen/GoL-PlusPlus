#include <GameOfLife.hpp>

GameOfLife::GameOfLife(unsigned int window_width, unsigned int window_height, unsigned int cell_size, float tick_rate)
    : window_(sf::VideoMode({window_width, window_height}), "Game of Life++"),
      grid_(window_width, window_height, cell_size),
      running_(false),
      tick_rate_(tick_rate),
      accumulator_(0.0f) {
    window_.setFramerateLimit(60);
    window_width_ = window_width;
    window_height_ = window_height;
    cell_size_ = cell_size;
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
                int cell_x = mouse_pos.x / cell_size_;
                int cell_y = mouse_pos.y / cell_size_;

                if (cell_x >= 0 && cell_x < grid_.GetWidth() && cell_y >= 0 && cell_y < grid_.GetHeight())
                    grid_.ToggleCell(cell_y, cell_x);
            }
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