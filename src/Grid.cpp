#include <SFML/Graphics.hpp>
#include "Grid.hpp"

Grid::Grid(unsigned int window_width, unsigned int window_height, unsigned int cell_size)
    : width_(window_width / cell_size),
      height_(window_height / cell_size),
      cell_size_(cell_size),
      cells_(height_, std::vector<Cell>(width_)) {
    grid_lines_ = CreateGridLines(window_width, window_height);
}

void Grid::Update() {
    std::vector<std::vector<Cell>> next_cells = cells_;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const Cell& current_cell = cells_[y][x];
            Cell& next_cell = next_cells[y][x];
            int alive_neighbors = CountAliveNeighbors(y, x);

            if (current_cell.IsAlive()) {
                if (alive_neighbors < 2 || alive_neighbors > 3)
                    next_cell = Cell(false, current_cell.GetColorAlive(), current_cell.GetColorDead());
                else
                    next_cell = Cell(true, current_cell.GetColorAlive(), current_cell.GetColorDead());
            } else {
                if (alive_neighbors == 3)
                    next_cell = Cell(true, current_cell.GetColorAlive(), current_cell.GetColorDead());
                else
                    next_cell = Cell(false, current_cell.GetColorAlive(), current_cell.GetColorDead());
            }
        }
    }

    cells_ = next_cells;
}

void Grid::Render(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(cell_size_), static_cast<float>(cell_size_)));
    
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const Cell& cell = cells_[y][x];
            rectangle.setPosition({static_cast<float>(x * cell_size_), static_cast<float>(y * cell_size_)});
            rectangle.setFillColor(cell.IsAlive() ? cell.GetColorAlive() : cell.GetColorDead());
            window.draw(rectangle);
        }
    }

    window.draw(grid_lines_);
}

sf::VertexArray Grid::CreateGridLines(unsigned int window_width_, unsigned int window_height_) {
    sf::VertexArray lines(sf::PrimitiveType::Lines);

    for (int y = 0; y <= height_; ++y) {
        float y_pos = y * cell_size_;
        lines.append({sf::Vector2f(0, y_pos), sf::Color::Black});
        lines.append({sf::Vector2f(static_cast<float>(window_width_), y_pos), sf::Color::Black});
    }

    for (int x = 0; x <= width_; ++x) {
        float x_pos = x * cell_size_;
        lines.append({sf::Vector2f(x_pos, 0), sf::Color::Black});
        lines.append({sf::Vector2f(x_pos, static_cast<float>(window_height_)), sf::Color::Black});
    }

    return lines;
}

int Grid::CountAliveNeighbors(unsigned int y, unsigned int x) {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy)
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            unsigned int nx = x + dx;
            unsigned int ny = y + dy;
            if (ny < height_ && nx < width_ && cells_[ny][nx].IsAlive())
                count++;
        }

    return count;
}

void Grid::ToggleCell(unsigned int y, unsigned int x) {
    if (y < height_ && x < width_)
        cells_[y][x].Toggle();
}
