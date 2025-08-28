#pragma once

#include "Animal.hpp"

class Grid;
class Pack;

class Human : public Animal {
public:
    Human(int hp, int max_hp, int hunger, int max_hunger, int damage, Pack* pack = nullptr);
    void Update(Grid& grid, int y, int x) override;
    EntityType Type() const override { return EntityType::kHuman;}

    std::unique_ptr<Entity> Clone() const override {
        return std::make_unique<Human>(hp_, max_hp_, hunger_, max_hunger_, damage_, nullptr); // TODO: Fix Pack logic
    }

private:
    Pack* pack_;
};
