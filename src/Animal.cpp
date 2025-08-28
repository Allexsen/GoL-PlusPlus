#include "Entity.hpp"
#include "Animal.hpp"
#include "Cell.hpp"
#include "Pack.hpp"

Animal::Animal(int hp, int max_hp, int hunger, int max_hunger, int damage, Pack* pack)
    : hp_(hp), max_hp_(max_hp), hunger_(hunger), max_hunger_(max_hunger), damage_(damage), pack_(pack) {
        if (!pack) {
            pack_ = new Pack();
        } 
        pack_->AddMember();

        if (hp_ > max_hp_) hp_ = max_hp_;
        if (hunger_ > max_hunger_) hunger_ = max_hunger_;
    }

bool Animal::TakeDamage(int damage) {
    hp_ -= damage;
    return hp_ <= 0; // Return true if the animal is dead
}

void Animal::Attack(std::vector<std::vector<Cell>>& cells, std::vector<std::vector<Cell>>& next_cells, int y, int x) {
    if (hp_ <= 0) return;  // If the animal is dead, it can't attack

    int plant_y = -1;
    int plant_x = -1;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dy == 0 && dx == 0) continue; // Skip the current cell
            int ny = y + dy;
            int nx = x + dx;
            if (ny >= 0 && ny < cells.size() && nx >= 0 && nx < cells[0].size()) {
                Cell& neighbor_cell = next_cells[ny][nx];
                if (!neighbor_cell.IsAlive() || !neighbor_cell.GetEntity()) {
                    continue;
                }

                Animal* target = dynamic_cast<Animal*>(neighbor_cell.GetEntity());
                if (target) {
                    if (target->Type() == this->Type()) {
                        continue; // Skip if the target is of the same type
                    }

                    bool is_dead = target->TakeDamage(damage_);
                    if (is_dead) {
                        neighbor_cell.RemoveEntity();
                        this->Feed();
                    }

                    return; // Attack the first enemy, stop further searching
                } else if (plant_y == -1 && neighbor_cell.GetEntity()->Type() == EntityType::kPlant) {
                    plant_y = ny;
                    plant_x = nx;
                }
            }
        }
    }

    // If no Animal was attacked, try to eat a Plant
    if (plant_y != -1 && plant_x != -1) {
        Cell& plant_cell = next_cells[plant_y][plant_x];
        this->Feed();
        plant_cell.RemoveEntity();
    }
}

void Animal::Feed() {
    hunger_ = max_hunger_;
}

int Animal::SetPack(Pack* pack) {
    pack_ = pack;
    if (pack) {
        pack->AddMember();
    }
    return pack_->GetSize();
}