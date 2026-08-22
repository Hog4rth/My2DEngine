#include "MovementSystem.h"

void MovementSystem::UpdatePosition(TagComponent tags[], PositionComponent positions[], VelocityComponent velocities[], float deltaTime, const int MAX_ECS_ENTITIES) {
	for (int i = 0; i < MAX_ECS_ENTITIES; ++i) {

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
