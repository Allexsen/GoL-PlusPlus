#include "Human.hpp"
#include "Animal.hpp"
#include "Grid.hpp"

Human::Human(int hp, int max_hp, int hunger, int max_hunger, int damage, Pack* pack)
    : Animal(hp, max_hp, hunger, max_hunger, damage, pack) {}

void Human::Update(Grid& grid, int y, int x) {
    
}
