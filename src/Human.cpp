#include "Human.hpp"
#include "Animal.hpp"
#include "Grid.hpp"

Human::Human(int hp, int hunger, int damage)
    : Animal(hp, hunger, damage) {}

void Human::Update(Grid& grid, int y, int x) {
    
}
