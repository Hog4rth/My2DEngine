#include "CollisionSystem.h"

void CollisionSystem::UpdateCollisions(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes, std::span<CollisionComponent> colliders, std::span<VelocityComponent> velocities, const float deltaTime) {

	for (size_t i = 0; i < tags.size(); ++i) {

		if (tags[i].id == EntityTag::None) {
			continue;
		}

		if (!velocities[i].canItMove) { // check if i-object can move 
			continue;
		}

		colliders[i].onTheLeftWall = false;
		colliders[i].onTheRightWall = false;
		colliders[i].isOnTheGround = false;


		for (size_t j = 0; j < colliders.size(); ++j) {
			if (i == j || !colliders[j].isSolid) { // check if j-object is solid and not the same as i-object
				continue;
			}

			float futurePositionX = positions[i].x + velocities[i].velocityX * deltaTime;

			if (futurePositionX + sizes[i].width > positions[j].x &&
				positions[j].x + sizes[j].width > futurePositionX &&
				positions[i].y + sizes[i].height > positions[j].y &&
				positions[j].y + sizes[j].height > positions[i].y) { // if the future position.x and the current position.y of i-object is colliding with j-object

				if (velocities[i].velocityX > 0) { // and if i-object is moving right
					velocities[i].velocityX = (positions[j].x - positions[i].x - sizes[i].width) / deltaTime; // adjust the velocity to stop at the left edge of j-object
					colliders[i].onTheRightWall = true;
				}
				else if (velocities[i].velocityX < 0) { // and if i-object is moving left
					velocities[i].velocityX = (positions[j].x + sizes[j].width - positions[i].x) / deltaTime; // adjust the velocity to stop at the right edge of j-object
					colliders[i].onTheLeftWall = true;
				}
			}

			futurePositionX = positions[i].x + velocities[i].velocityX * deltaTime; // Calculate again because velocity may have changed
			float futurePositionY = positions[i].y + velocities[i].velocityY * deltaTime;

			if (futurePositionX + sizes[i].width > positions[j].x &&
				positions[j].x + sizes[j].width > futurePositionX &&
				futurePositionY + sizes[i].height > positions[j].y &&
				positions[j].y + sizes[j].height > futurePositionY) { // if the future position.x and the future position.y of i-object is colliding with j-object
				// Note: Now we can use future position.y because we have already adjusted the velocity.x if there was a collision in the previous step

				if (velocities[i].velocityY > 0) { // and if i-object is moving down
					velocities[i].velocityY = (positions[j].y - positions[i].y - sizes[i].height) / deltaTime; // adjust the velocity to stop at the top edge of j-object
					colliders[i].isOnTheGround = true;
				}
				else if (velocities[i].velocityY < 0) { // and if i-object is moving up
					velocities[i].velocityY = (positions[j].y + sizes[j].height - positions[i].y) / deltaTime; // adjust the velocity to stop at the bottom edge of j-object
				}
			}
		}
	}
}
