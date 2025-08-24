#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.hpp"

class Cell {
public:
    Cell();
    Cell(bool alive, std::unique_ptr<Entity> entity = nullptr);
    ~Cell();

    // Enable copy semantics
    Cell(const Cell& other);
    Cell& operator=(const Cell& other);

    // Add move semantics
    Cell(Cell&&) noexcept;
    Cell& operator=(Cell&&) noexcept;

    bool IsAlive() const { return alive_; } // TODO: Move IsAlive() logic to Entity

    // Alpha ranges from 20% (alive but low HP) to 100% (full HP)
    sf::Color GetColor() const;

    Entity* GetEntity() const { return entity_.get(); }
    void SetEntity(std::unique_ptr<Entity> entity);
    void RemoveEntity();

private:
    bool alive_;
    sf::Color color_;
    std::unique_ptr<Entity> entity_;
};