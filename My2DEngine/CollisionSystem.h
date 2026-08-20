#pragma once
#include "Components.h"

class CollisionSystem {
public:
	static void UpdateCollisions(TagComponent tags[], PositionComponent positions[], SizeComponent sizes[], CollisionComponent colliders[], VelocityComponent velocities[], float deltaTime, const int MAX_ECS_ENTITIES);

};



