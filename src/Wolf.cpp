#include "Wolf.hpp"
#include "Grid.hpp"
#include "Animal.hpp"

Wolf::Wolf(int hp, int max_hp, int hunger, int max_hunger, int damage, Pack* pack)
    : Animal(hp, max_hp, hunger, max_hunger, damage, pack) {}

void Wolf::Update(Grid& grid, int y, int x) {
    // TODO: Implement Wolf's update behavior
}
