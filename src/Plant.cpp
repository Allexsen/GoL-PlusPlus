#include <vector>
#include "Plant.hpp"
#include "Cell.hpp"
#include "Grid.hpp"

Plant::Plant(int hp) : hp_(hp), max_hp_(100), damage_(5) {
    if (hp_ > max_hp_) hp_ = max_hp_;
}

void Plant::Update(Grid& grid, int y, int x) {
    // TODO: Define plant behavior
}

void Plant::Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) {
    if (hp_ * 2 < max_hp_) return;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            unsigned int nx = x + dx;
            unsigned int ny = y + dy;
            if (ny < cells.size() && nx < cells[ny].size() &&
                cells[ny][nx].IsAlive() &&
                cells[ny][nx].GetEntity()->Type() == EntityType::kWall &&
                next_cells[ny][nx].IsAlive()) {
                    bool is_dead = next_cells[ny][nx].GetEntity()->TakeDamage(damage_);
                    if (is_dead) {
                        next_cells[ny][nx].RemoveEntity();
                        next_cells[ny][nx].SetEntity(std::make_unique<Plant>(10));
                    }
            }
        }
    }
}

void Plant::Heal() {
    hp_ += (max_hp_ / 10);
    if (hp_ > max_hp_) {
        hp_ = max_hp_;
    }
}

bool Plant::TakeDamage(int damage) {
    hp_ -= damage;
    return hp_ <= 0;
}