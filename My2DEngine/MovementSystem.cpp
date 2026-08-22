#include "MovementSystem.h"

void MovementSystem::UpdatePosition(std::span<const TagComponent> tags, std::span<PositionComponent> positions, std::span<const VelocityComponent> velocities, const float deltaTime) {
	for (size_t i = 0; i < tags.size(); ++i) {

		if (tags[i].id == EntityTag::None) {
			continue;
		}

		if (!velocities[i].canItMove) {
			continue;
		}

		positions[i].x += velocities[i].velocityX * deltaTime;
		positions[i].y += velocities[i].velocityY * deltaTime;
	}
}
