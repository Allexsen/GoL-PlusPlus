#pragma once

#include "Entity.hpp"

class Plant : public Entity {
public:
    Plant(int x, int y);
    void grow();
};
