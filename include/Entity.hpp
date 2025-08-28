#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Colors.hpp"

class Grid;
class Cell;

enum class EntityType {
    kWolf,
    kHuman,
    kPlant,
    kWall
};

inline sf::Color GetEntityColor(EntityType type) {
    switch (type) {
        case EntityType::kWolf:  return Colors::kWolfColor;
        case EntityType::kHuman:  return Colors::kHumanColor;
        case EntityType::kPlant:  return Colors::kPlantColor;
        case EntityType::kWall:   return Colors::kWallColor;
        default:                  return Colors::kBackgroundColor;
    }
}

class Entity {
public:
    Entity() = default;
    virtual ~Entity() = default;
    virtual void Update(Grid& grid, int y, int x) = 0;
    virtual EntityType Type() const = 0;
    virtual int GetHP() const = 0;
    virtual bool TakeDamage(int damage) = 0;
    virtual void Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) = 0;

    // Virtual clone
    virtual std::unique_ptr<Entity> Clone() const = 0;
};