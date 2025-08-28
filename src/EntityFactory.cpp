#include "EntityFactory.hpp"
#include "Wolf.hpp"
#include "Human.hpp"
#include "Plant.hpp"
#include "Wall.hpp"

std::unique_ptr<Entity> EntityFactory::CreateWolf() {
    return std::make_unique<Wolf>(
        EntityConfig::Wolf::kHP,
        EntityConfig::Wolf::kMaxHP,
        EntityConfig::Wolf::kHunger,
        EntityConfig::Wolf::kMaxHunger,
        EntityConfig::Wolf::kDamage
    );
}

std::unique_ptr<Entity> EntityFactory::CreateHuman() {
    return std::make_unique<Human>(
        EntityConfig::Human::kHP,
        EntityConfig::Human::kMaxHP,
        EntityConfig::Human::kHunger,
        EntityConfig::Human::kMaxHunger,
        EntityConfig::Human::kDamage
    );
}

std::unique_ptr<Entity> EntityFactory::CreatePlant() {
    return std::make_unique<Plant>(
        EntityConfig::Plant::kHP,
        EntityConfig::Plant::kMaxHP,
        EntityConfig::Plant::kDamage
    );
}

std::unique_ptr<Entity> EntityFactory::CreateWall() {
    return std::make_unique<Wall>(
        EntityConfig::Wall::kHP,
        EntityConfig::Wall::kMaxHP
    );
}
