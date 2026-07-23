#pragma once
#include "Components.h"

class MovementSystem {
public:
    
    static void Update(PositionComponent positions[], VelocityComponent velocities[], int maxEntities, float deltaTime);
};
