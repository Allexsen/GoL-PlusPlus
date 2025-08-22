#pragma once

#include "Animal.hpp"

class Grid;
class Pack;

class Human : public Animal {
public:
    Human(int hp, int hunger, int damage);
    void Update(Grid& grid, int y, int x) override;
    EntityType Type() const override { return EntityType::kHuman;}

    std::unique_ptr<Entity> Clone() const override {
        return std::make_unique<Human>(hp_, hunger_, damage_);
    }

private:
    Pack* pack_;
};
