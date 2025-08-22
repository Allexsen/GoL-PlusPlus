#include "Entity.hpp"
#include "Animal.hpp"
#include "Cell.hpp"
#include "Pack.hpp"

Animal::Animal(int hp, int hunger, int damage, Pack* pack)
    : hp_(hp), hunger_(hunger), damage_(damage), pack_(pack) {
        if (!pack) {
            pack_ = new Pack();
        } 
        pack_->AddMember();
    }

bool Animal::TakeDamage(int damage) {
    hp_ -= damage;
    return hp_ <= 0; // Return true if the animal is dead
}

void Animal::Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) {
    if (hp_ <= 0) return;  // If the animal is dead, it can't attack

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dy == 0 && dx == 0) continue; // Skip the current cell
            int ny = y + dy;
            int nx = x + dx;
            if (ny >= 0 && ny < cells.size() && nx >= 0 && nx < cells[0].size()) {
                Cell& current_cell = cells[y][x];
                Cell& neighbor_cell = next_cells[ny][nx];
                if (neighbor_cell.IsAlive() && neighbor_cell.GetEntity() &&
                    neighbor_cell.GetEntity()->Type() != current_cell.GetEntity()->Type() &&
                    neighbor_cell.GetEntity()->Type() != EntityType::kWall) {
                        bool is_dead = neighbor_cell.GetEntity()->TakeDamage(damage_);
                        if (is_dead) {
                            neighbor_cell.RemoveEntity();
                        }

                        return; // Attack the first enemy, stop further searching
                }
            }
        }
    }
}

int Animal::SetPack(Pack* pack) {
    pack_ = pack;
    if (pack) {
        pack->AddMember();
    }
    return pack_->GetSize();
}