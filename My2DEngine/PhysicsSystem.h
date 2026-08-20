#pragma once
#include "Components.h"

class PhysicsSystem {
public:
	static void CalculateTrajectory(TagComponent tags[], InputComponent inputs[], CollisionComponent colliders[], VelocityComponent velocities[], float deltaTime, const int MAX_ECS_ENTITIES);

};