#pragma once
#include "Components.h"

class CollisionSystem {
public:
	static void UpdateCollisions(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes, std::span<CollisionComponent> colliders, std::span<VelocityComponent> velocities, const float deltaTime);

};
