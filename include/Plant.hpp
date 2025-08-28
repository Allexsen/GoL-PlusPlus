#pragma once

#include "Entity.hpp"

class Plant : public Entity {
public:
    Plant(int hp, int max_hp, int damage_);
    void Update(Grid& grid, int y, int x) override;
    EntityType Type() const override { return EntityType::kPlant; }

    int GetHP() const { return hp_; }
    bool TakeDamage(int damage);
    void Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) override;
    void Heal();

    std::unique_ptr<Entity> Clone() const override {
        return std::make_unique<Plant>(hp_, max_hp_, damage_);
    }

private:
    int hp_;
    int max_hp_;
    int damage_;
};
