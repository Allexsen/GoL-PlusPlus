#pragma once

#include <vector>
#include "Entity.hpp"

class Pack;
class Cell;
class Grid;

class Animal : public Entity {
public:
    Animal(int hp, int max_hp, int hunger, int max_hunger, int damage, Pack* pack = nullptr);
    int GetHP() const { return hp_; }
    int GetHunger() const { return hunger_; }
    int GetDamage() const { return damage_; }
    int SetPack(Pack* pack);
    // TODO: Pack* GetPack() const { return pack_; }
    
    void Feed();
    bool TakeDamage(int damage) override;
    void Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) override;

    virtual void Update(Grid& grid, int y, int x) = 0;

    // Add Clone method (still pure virtual since Animal is abstract)
    std::unique_ptr<Entity> Clone() const override = 0;
    
protected:
    int hp_;
    int max_hp_;
    int hunger_;
    int max_hunger_;
    int damage_;
    Pack* pack_ = nullptr;
};