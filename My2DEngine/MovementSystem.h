#pragma once
#include "Components.h"

class MovementSystem {
public:

	static void UpdatePosition(std::span<const TagComponent> tags, std::span<PositionComponent> positions, std::span<const VelocityComponent> velocities, const float deltaTime);
};
