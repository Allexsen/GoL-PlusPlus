#include "Wall.hpp"

Wall::Wall(int hp) : max_hp_(200), hp_(hp) {
    if (hp_ > max_hp_) hp_ = max_hp_;
}

void Wall::Update(Grid& grid, int y, int x) {
    // Walls don't move or change
}

bool Wall::TakeDamage(int damage) {
    hp_ -= damage;
    return hp_ <= 0;
}

void Wall::Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) {
    // Walls don't attack
}
