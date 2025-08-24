#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Grid.hpp"
#include "Human.hpp"
#include "Wolf.hpp"
#include "Plant.hpp"
#include "Cell.hpp"

Grid::Grid(unsigned int window_width, unsigned int window_height, unsigned int cell_size)
    : width_(window_width / cell_size),
      height_(window_height / cell_size),
      cell_size_(cell_size),
      cells_(height_, std::vector<Cell>(width_)) {
    grid_lines_ = CreateGridLines(window_width, window_height);
}

void Grid::Update() {
    // TODO: Review copying. This can be done without copying.
    // next_cells are only accessed to update - not to read. It can be empty.
    std::vector<std::vector<Cell>> next_cells = cells_;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const Cell& current_cell = cells_[y][x];
            Cell& next_cell = next_cells[y][x];

            if (current_cell.IsAlive() && current_cell.GetEntity()) {
                current_cell.GetEntity()->Attack(cells_, next_cells, y, x);

                if (current_cell.GetEntity()->Type() == EntityType::kPlant &&
                    next_cell.IsAlive() &&
                    next_cell.GetEntity()->Type() == EntityType::kPlant) {
                        Plant* plant = dynamic_cast<Plant*>(next_cell.GetEntity());
                        plant->Heal();
                }
            }
        }
    }

    cells_ = next_cells;
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            Cell& current_cell = cells_[y][x];
            Cell& next_cell = next_cells[y][x];
            
            if (current_cell.IsAlive()) {
                EntityType type = current_cell.GetEntity()->Type();
                if (type == EntityType::kWall || type == EntityType::kPlant) {
                    continue; // Walls and plants don't die out.
                }

                int alive_neighbors = CountAliveNeighbors(y, x, type);
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    next_cell.RemoveEntity();
                }
            } else {
                if (CountAliveNeighbors(y, x, EntityType::kWolf) == 3) {
                    next_cell.SetEntity(std::make_unique<Wolf>(100, 3, 70));
                } else if (CountAliveNeighbors(y, x, EntityType::kHuman) == 3) {
                    next_cell.SetEntity(std::make_unique<Human>(100, 5, 30));
                } else if (CountAliveNeighbors(y, x, EntityType::kPlant) == 3) {
                    next_cell.SetEntity(std::make_unique<Plant>(100));
                }
            }
        }
    }

    cells_ = next_cells;
}

void Grid::UpdateCell(unsigned int y, unsigned int x, std::unique_ptr<Entity> entity) {
    if (x < width_ && y < height_) {
        cells_[y][x].SetEntity(std::move(entity));
    }
}

void Grid::EmptyCell(unsigned int y, unsigned int x) {
    if (x < width_ && y < height_) {
        cells_[y][x].RemoveEntity();
    }
}

void Grid::UpdatePacks() {
    for (unsigned int y = 0; y < height_; ++y) {
        for (unsigned int x = 0; x < width_; ++x) {
            Cell& cell = cells_[y][x];
            if (cell.IsAlive()) {
                // TODO: Pack Logic once Packs are introduced
            }
        }
    }
}

void Grid::Render(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(cell_size_), static_cast<float>(cell_size_)));
    
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const Cell& cell = cells_[y][x];
            rectangle.setPosition({static_cast<float>(x * cell_size_), static_cast<float>(y * cell_size_)});
            rectangle.setFillColor(cell.GetColor());
            window.draw(rectangle);
        }
    }

    window.draw(grid_lines_);
}

int Grid::CountAliveNeighbors(unsigned int y, unsigned int x, EntityType type) {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy)
    for (int dx = -1; dx <= 1; ++dx) {
        if (dx == 0 && dy == 0) continue; // Skip the cell itself
        unsigned int nx = x + dx;
        unsigned int ny = y + dy;
        if (ny < height_ && nx < width_ && cells_[ny][nx].IsAlive() && cells_[ny][nx].GetEntity()->Type() == type)
        count++;
    }
    
    return count;
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