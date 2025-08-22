#pragma once

#include "Animal.hpp"

class Grid;
class Pack;

class Wolf : public Animal {
public:
    Wolf(int hp, int hunger, int damage);
    void Update(Grid& grid, int y, int x) override;
    EntityType Type() const override { return EntityType::kWolf;}

    std::unique_ptr<Entity> Clone() const override {
        return std::make_unique<Wolf>(hp_, hunger_, damage_);
    }

private:
    Pack* pack_;
};