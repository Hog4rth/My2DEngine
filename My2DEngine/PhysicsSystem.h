#pragma once
#include "Components.h"

class PhysicsSystem {
public:
	static void CalculateTrajectory(const TagComponent tags[], const InputComponent inputs[], const CollisionComponent colliders[], VelocityComponent velocities[], KinematicComponent kinematics[], const float deltaTime, const int MAX_ECS_ENTITIES);

};
