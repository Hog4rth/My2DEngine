#pragma once
#include "Components.h"

class MovementSystem {
public:

    static void UpdatePosition(TagComponent tags[], PositionComponent positions[], VelocityComponent velocities[], float deltaTime, const int MAX_ECS_ENTITIES);
};
