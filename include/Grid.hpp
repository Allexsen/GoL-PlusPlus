#pragma once

#include <SFML/Graphics.hpp>
#include <Cell.hpp>

class Grid {
public:
    Grid(unsigned int width, unsigned int height, unsigned int cell_size);
    void Update();
    void Render(sf::RenderWindow& window);

    unsigned int GetWidth() const { return width_; }
    unsigned int GetHeight() const { return height_; }
    unsigned int GetCellSize() const { return cell_size_; }
    std::vector<std::vector<Cell>>& GetCells() { return cells_; }

    int CountAliveNeighbors(unsigned int x, unsigned int y);
    void ToggleCell(unsigned int y, unsigned int x);

private:
    unsigned int width_;
    unsigned int height_;
    unsigned int cell_size_;
    sf::VertexArray grid_lines_;
    std::vector<std::vector<Cell>> cells_;

    sf::VertexArray CreateGridLines(unsigned int window_width, unsigned int window_height);
};
