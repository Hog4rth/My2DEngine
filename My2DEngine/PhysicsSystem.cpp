#include "PhysicsSystem.h"

void PhysicsSystem::CalculateTrajectory(std::span<const TagComponent> tags, std::span<const InputComponent> inputs, std::span<const CollisionComponent> colliders, std::span<VelocityComponent> velocities, std::span<KinematicComponent> kinematics, const float deltaTime) {
	for (size_t i = 0; i < tags.size(); ++i) {

		if (tags[i].id == EntityTag::None) {
			continue;
		}

		if (!velocities[i].canItMove) {
			continue;
		}

		if (tags[i].id == EntityTag::Player) {

			CalculateHorizontalVelocity(inputs[i].direction, velocities[i], kinematics[i], deltaTime);
			UpdateJumpTimers(colliders[i], inputs[i], kinematics[i], deltaTime);
			CalculateVerticalVelocity(colliders[i], velocities[i], kinematics[i]);

		}

		// Apply gravity
		velocities[i].velocityY += kinematics[i].gravity * deltaTime;
	}
}

// --- Helpers ---

void PhysicsSystem::CalculateHorizontalVelocity(const float currentDirection, VelocityComponent& velocity, const KinematicComponent& kinematic, const float deltaTime) {

	if (currentDirection == 0 || (currentDirection == 1 && velocity.velocityX < 0) || (currentDirection == -1 && velocity.velocityX > 0)) { // Apply friction when no input is given or when the input direction is opposite to the current velocity
		if (velocity.velocityX > 0) { // Apply friction going left
			velocity.velocityX -= kinematic.friction * deltaTime;
			if (velocity.velocityX < 0) {
				velocity.velocityX = 0;
			}
		}
		else if (velocity.velocityX < 0) { // Apply friction going right
			velocity.velocityX += kinematic.friction * deltaTime;
			if (velocity.velocityX > 0) {
				velocity.velocityX = 0;
			}
		}
	}
	else {
		velocity.velocityX += currentDirection * kinematic.acceleration * deltaTime; // Update velocity based on input direction and acceleration

		if (velocity.velocityX > kinematic.maxSpeed) {
			velocity.velocityX = kinematic.maxSpeed;
		}
		else if (velocity.velocityX < -kinematic.maxSpeed) {
			velocity.velocityX = -kinematic.maxSpeed;
		}
	}

}

void PhysicsSystem::UpdateJumpTimers(const CollisionComponent& collider, const InputComponent& input, KinematicComponent& kinematic, const float deltaTime) {

	// --- Jump Buffer ---

	if (kinematic.jumpBufferTimer > 0) {
		kinematic.jumpBufferTimer -= deltaTime;

	}
	else {
		kinematic.jumpBufferTimer = 0;
	}

	if (input.isJumping && !input.wasJumping) {
		kinematic.jumpBufferTimer = kinematic.jumpBufferDuration;
	}

	// --- Jump Coyote ---

	if (kinematic.jumpCoyoteTimer > 0) {
		kinematic.jumpCoyoteTimer -= deltaTime;

	}
	else {
		kinematic.jumpCoyoteTimer = 0;
	}

	if (collider.isOnTheGround) {
		kinematic.jumpCoyoteTimer = kinematic.jumpCoyoteDuration;
	}

}

void PhysicsSystem::CalculateVerticalVelocity(const CollisionComponent& collider, VelocityComponent& velocity, KinematicComponent& kinematic) {

	if (kinematic.jumpBufferTimer > 0) {

		if (!collider.isOnTheGround && collider.onTheLeftWall) { // Left Wall Jump
			velocity.velocityY = -kinematic.jumpForceY;
			velocity.velocityX = kinematic.jumpForceX;

			kinematic.jumpBufferTimer = 0;
			kinematic.jumpCoyoteTimer = 0;
		}
		else if (!collider.isOnTheGround && collider.onTheRightWall) { // Right Wall Jump
			velocity.velocityY = -kinematic.jumpForceY;
			velocity.velocityX = -kinematic.jumpForceX;

			kinematic.jumpBufferTimer = 0;
			kinematic.jumpCoyoteTimer = 0;
		}
		else if (kinematic.jumpCoyoteTimer > 0) { // Ground jump
			velocity.velocityY = -kinematic.jumpForceY;

			kinematic.jumpBufferTimer = 0;
			kinematic.jumpCoyoteTimer = 0;
		}
	}

}
