#pragma once
#include "Components.h"

class MovementSystem {
public:

	static void UpdatePosition(const TagComponent tags[], PositionComponent positions[], const VelocityComponent velocities[], const float deltaTime, const int MAX_ECS_ENTITIES);
};
