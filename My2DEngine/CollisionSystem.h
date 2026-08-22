#pragma once
#include "Components.h"

class CollisionSystem {
public:
	static void UpdateCollisions(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], CollisionComponent colliders[], VelocityComponent velocities[], const float deltaTime, const int MAX_ECS_ENTITIES);

};
