#pragma once
#include "Components.h"

class PhysicsSystem {
public:
	static void CalculateTrajectory(std::span<const TagComponent> tags, std::span<const InputComponent> inputs, std::span<const CollisionComponent> colliders, std::span<VelocityComponent> velocities, std::span<KinematicComponent> kinematics, const float deltaTime);

};
