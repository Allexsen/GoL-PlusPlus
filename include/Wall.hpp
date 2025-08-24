#pragma once

#include "Entity.hpp"

class Wall : public Entity {
public:
    Wall(int hp);
    void Update(Grid& grid, int y, int x) override;
    int GetHP() const override { return hp_; }
    bool TakeDamage(int damage) override;
    EntityType Type() const override { return EntityType::kWall; }
    void Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) override;

    std::unique_ptr<Entity> Clone() const override {
        return std::make_unique<Wall>(hp_);
    }
private:
    int hp_;
    int max_hp_;
};
