#pragma once
#include <algorithm>
#include "Components.h"

class PhysicsSystem {
public:
	static void CalculateTrajectory(std::span<const TagComponent> tags, std::span<const InputComponent> inputs, std::span<const CollisionComponent> colliders, std::span<VelocityComponent> velocities, std::span<KinematicComponent> kinematics, const float deltaTime);

private:
	static void UpdateJumpTimers(const CollisionComponent& collider, const InputComponent& input, KinematicComponent& kinematic, const float deltaTime);
	static void CalculateHorizontalVelocity(const float currentDirection, const CollisionComponent& collider, VelocityComponent& velocity, const KinematicComponent& kinematic, const float deltaTime);
	static void CalculateVerticalVelocity(const CollisionComponent& collider, VelocityComponent& velocity, KinematicComponent& kinematic, const float deltaTime);

};
