#include "CollisionSystem.h"

struct Rect {
	float x, y, w, h;
	float Right() const { return x + w; }
	float Bottom() const { return y + h; }

	bool Overlaps(const Rect& o) const {
		return Right() > o.x && o.Right() > x && Bottom() > o.y && o.Bottom() > y;
	}
};

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


		for (size_t j = 0; j < tags.size(); ++j) {
			if (i == j || !colliders[j].isSolid) { // check if j-object is solid and not the same as i-object
				continue;
			}

			float futurePositionX = positions[i].x + velocities[i].velocityX * deltaTime;

			Rect rectI_X = { futurePositionX, positions[i].y, sizes[i].width, sizes[i].height };
			Rect rectJ = { positions[j].x, positions[j].y, sizes[j].width, sizes[j].height };

			if (rectI_X.Overlaps(rectJ)) {

				if (velocities[i].velocityX > 0) { // if i-object is moving right
					velocities[i].velocityX = (positions[j].x - positions[i].x - sizes[i].width) / deltaTime; // adjust the velocity to stop at the left edge of j-object
					colliders[i].onTheRightWall = true;
				}
				else if (velocities[i].velocityX < 0) { // if i-object is moving left
					velocities[i].velocityX = (positions[j].x + sizes[j].width - positions[i].x) / deltaTime; // adjust the velocity to stop at the right edge of j-object
					colliders[i].onTheLeftWall = true;
				}
			}

			futurePositionX = positions[i].x + velocities[i].velocityX * deltaTime; // Calculate again because velocity may have changed
			float futurePositionY = positions[i].y + velocities[i].velocityY * deltaTime;

			Rect rectI_Y = { futurePositionX, futurePositionY, sizes[i].width, sizes[i].height };

			if (rectI_Y.Overlaps(rectJ)) { // Note: Now we can use future position.y because we have already adjusted the velocity.x if there was a collision in the previous step

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
