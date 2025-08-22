#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.hpp"

class Entity;
enum class EntityType;

class Grid {
public:
    Grid(unsigned int width, unsigned int height, unsigned int cell_size);
    void Update();
    void Render(sf::RenderWindow& window);

    unsigned int GetWidth() const { return width_; }
    unsigned int GetHeight() const { return height_; }
    unsigned int GetCellSize() const { return cell_size_; }
    std::vector<std::vector<Cell>>& GetCells() { return cells_; }
    
    void UpdatePacks();
    void UpdateCell(unsigned int x, unsigned int y, std::unique_ptr<Entity> entity);
    void EmptyCell(unsigned int x, unsigned int y);
    int CountAliveNeighbors(unsigned int x, unsigned int y, EntityType type);

private:
    unsigned int width_;
    unsigned int height_;
    unsigned int cell_size_;
    sf::VertexArray grid_lines_;
    std::vector<std::vector<Cell>> cells_;

    sf::VertexArray CreateGridLines(unsigned int window_width, unsigned int window_height);
};
