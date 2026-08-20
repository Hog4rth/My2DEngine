#include "PhysicsSystem.h"

void PhysicsSystem::CalculateTrajectory(TagComponent tags[], InputComponent inputs[], CollisionComponent colliders[], VelocityComponent velocities[], float deltaTime, const int MAX_ECS_ENTITIES) {
	for (int i = 0; i < MAX_ECS_ENTITIES; ++i) {

		if (tags[i].id == EntityTag::None) {
			continue;
		}

		if (!velocities[i].canItMove) {
			continue;
		}

		// --- Player: Horizontal Movement ---
		if (tags[i].id == EntityTag::Player) {

			float currentDir = inputs[i].direction;

			if (currentDir == 0 || (currentDir == 1 && velocities[i].vx < 0) || (currentDir == -1 && velocities[i].vx > 0)) { // Apply friction when no input is given or when the input direction is opposite to the current velocity
				if (velocities[i].vx > 0) { // Apply friction going left
					velocities[i].vx -= velocities[i].friction * deltaTime;
					if (velocities[i].vx < 0) {
						velocities[i].vx = 0;
					}
				}
				else if (velocities[i].vx < 0) { // Apply friction going right
					velocities[i].vx += velocities[i].friction * deltaTime;
					if (velocities[i].vx > 0) {
						velocities[i].vx = 0;
					}
				}
			}
			else {
				velocities[i].vx += currentDir * velocities[i].acceleration * deltaTime; // Update velocity based on input direction and acceleration

				if (velocities[i].vx > velocities[i].maxspeed) {
					velocities[i].vx = velocities[i].maxspeed;
				}
				else if (velocities[i].vx < -velocities[i].maxspeed) {
					velocities[i].vx = -velocities[i].maxspeed;
				}
			}


			// --- Jump Buffer Setup ---

			if (inputs[i].jumpBufferTimer > 0) {
				inputs[i].jumpBufferTimer -= deltaTime; // Update jump buffer timer

			}
			else {
				inputs[i].jumpBufferTimer = 0;
			}

			if (inputs[i].isJumping && !inputs[i].wasJumping) {
				inputs[i].jumpBufferTimer = inputs[i].jumpBufferDuration; // Reset jump buffer timer
			}

			// --- Jump Coyote Setup ---

			if (colliders[i].jumpCoyoteTimer > 0) {
				colliders[i].jumpCoyoteTimer -= deltaTime; // Update jump coyote timer

			}
			else {
				colliders[i].jumpCoyoteTimer = 0;
			}

			if (colliders[i].isOnTheGround) {
				colliders[i].jumpCoyoteTimer = colliders[i].jumpCoyoteDuration; // Reset jump coyote timer
			}

			// --- Player: Vertical Movement ---

			if (inputs[i].jumpBufferTimer > 0) {

				if (!colliders[i].isOnTheGround && colliders[i].onTheLeftWall) { // Left Wall Jump
					velocities[i].vy = -velocities[i].jumpForceY;
					velocities[i].vx = velocities[i].jumpForceX;

					inputs[i].jumpBufferTimer = 0;
					colliders[i].jumpCoyoteTimer = 0;
				}
				else if (!colliders[i].isOnTheGround && colliders[i].onTheRightWall) { // Right Wall Jump
					velocities[i].vy = -velocities[i].jumpForceY;
					velocities[i].vx = -velocities[i].jumpForceX;

					inputs[i].jumpBufferTimer = 0;
					colliders[i].jumpCoyoteTimer = 0;
				}
				else if (colliders[i].jumpCoyoteTimer > 0) { // Ground jump
					velocities[i].vy = -velocities[i].jumpForceY;

					inputs[i].jumpBufferTimer = 0;
					colliders[i].jumpCoyoteTimer = 0;
				}
			}

		}

		// --- Vertical Movement ---
		velocities[i].vy += velocities[i].gravity * deltaTime; // Apply gravity
	}
}