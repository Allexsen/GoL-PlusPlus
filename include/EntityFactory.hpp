#pragma once

#include "EntityConfig.hpp"
#include <memory>

class Entity;
class Wolf;
class Human;
class Plant;
class Wall;

class EntityFactory {
public:
    static std::unique_ptr<Entity> CreateWolf();
    static std::unique_ptr<Entity> CreateHuman();
    static std::unique_ptr<Entity> CreatePlant();
    static std::unique_ptr<Entity> CreateWall();
};