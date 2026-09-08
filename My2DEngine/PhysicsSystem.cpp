#include "PhysicsSystem.h"

#include <cstddef>

#include <algorithm>

void PhysicsSystem::CalculateTrajectory(std::span<const TagComponent> tags, std::span<const InputComponent> inputs,
                                        std::span<const CollisionComponent> colliders,
                                        std::span<VelocityComponent> velocities,
                                        std::span<KinematicComponent> kinematics, const float deltaTime) {
	for (size_t i = 0; i < tags.size(); ++i) {
		if (tags[i].id == EntityTag::None)
			continue;
		if (!velocities[i].canItMove)
			continue;

		if (tags[i].id == EntityTag::Player) {
			UpdateJumpTimers(colliders[i], inputs[i], kinematics[i], deltaTime);
			CalculateHorizontalVelocity(inputs[i].direction, colliders[i], velocities[i], kinematics[i], deltaTime);
			CalculateVerticalVelocity(colliders[i], velocities[i], kinematics[i], deltaTime);
		} else {
			velocities[i].velocityY += kinematics[i].gravity * deltaTime;

			if (velocities[i].velocityY >= kinematics[i].maxSpeedY) {
				velocities[i].velocityY = kinematics[i].maxSpeedY;
			}
		}
	}
}

// --- Helpers ---

void PhysicsSystem::UpdateJumpTimers(const CollisionComponent& collider, const InputComponent& input,
                                     KinematicComponent& kinematic, const float deltaTime) {
	// --- Wall Stick ---

	if (kinematic.wallStickTimer > deltaTime) {
		kinematic.wallStickTimer -= deltaTime;
	}
	if (kinematic.wallStickTimer <= deltaTime || collider.isOnTheGround) {
		kinematic.wallStickTimer = 0;
	}

	if (collider.onTheLeftWall && !collider.isOnTheGround && input.direction != 1 && kinematic.wallStickTimer == 0) {
		kinematic.wallStickTimer = kinematic.wallStickDuration;
	} else if (collider.onTheRightWall && !collider.isOnTheGround && input.direction != -1 &&
	           kinematic.wallStickTimer == 0) {
		kinematic.wallStickTimer = kinematic.wallStickDuration;
	}

	// --- Jump Buffer ---

	kinematic.jumpBufferTimer = (kinematic.jumpBufferTimer > deltaTime) ? kinematic.jumpBufferTimer - deltaTime : 0;

	if (input.isJumping && !input.wasJumping) {
		kinematic.jumpBufferTimer = kinematic.jumpBufferDuration;
	}

	// --- Jump Coyote ---

	kinematic.jumpCoyoteTimer = (kinematic.jumpCoyoteTimer > deltaTime) ? kinematic.jumpCoyoteTimer - deltaTime : 0;

	if (collider.isOnTheGround) {
		kinematic.jumpCoyoteTimer = kinematic.jumpCoyoteDuration;
	}
}

void PhysicsSystem::CalculateHorizontalVelocity(const float currentDirection, const CollisionComponent& collider,
                                                VelocityComponent& velocity, const KinematicComponent& kinematic,
                                                const float deltaTime) {
	if (kinematic.wallStickTimer > 0 && (collider.onTheLeftWall || collider.onTheRightWall)) {
		velocity.velocityX = 0.0f;
	} else {
		velocity.velocityX += currentDirection *
		                      (collider.isOnTheGround ? kinematic.groundAcceleration : kinematic.airAcceleration) *
		                      deltaTime;
	}
	// Apply friction when no input is given or when the input direction is opposite to the current velocity
	if (currentDirection == 0 || (currentDirection == 1 && velocity.velocityX < 0) ||
	    (currentDirection == -1 && velocity.velocityX > 0)) {
		if (velocity.velocityX > 0) {
			// Apply friction pointing left
			velocity.velocityX -=
			    (collider.isOnTheGround ? kinematic.groundFriction : kinematic.airFriction) * deltaTime;
			if (velocity.velocityX < 0) {
				velocity.velocityX = 0;
			}
		} else if (velocity.velocityX < 0) {
			// Apply friction pointing right
			velocity.velocityX +=
			    (collider.isOnTheGround ? kinematic.groundFriction : kinematic.airFriction) * deltaTime;
			if (velocity.velocityX > 0) {
				velocity.velocityX = 0;
			}
		}
	}
	velocity.velocityX = std::clamp(velocity.velocityX, -kinematic.maxSpeedX, kinematic.maxSpeedX);
}

void PhysicsSystem::CalculateVerticalVelocity(const CollisionComponent& collider, VelocityComponent& velocity,
                                              KinematicComponent& kinematic, const float deltaTime) {
	if (kinematic.jumpBufferTimer > 0) {
		bool hasJumped = false;

		if (!collider.isOnTheGround && collider.onTheLeftWall) {
			// Left Wall Jump
			velocity.velocityY = -kinematic.jumpForceY;
			velocity.velocityX = kinematic.jumpForceX;
			hasJumped = true;
		} else if (!collider.isOnTheGround && collider.onTheRightWall) {
			// Right Wall Jump
			velocity.velocityY = -kinematic.jumpForceY;
			velocity.velocityX = -kinematic.jumpForceX;
			hasJumped = true;
		} else if (kinematic.jumpCoyoteTimer > 0) {
			// Ground jump
			velocity.velocityY = -kinematic.jumpForceY;
			hasJumped = true;
		}
		if (hasJumped) {
			kinematic.jumpBufferTimer = 0;
			kinematic.jumpCoyoteTimer = 0;
			kinematic.wallStickTimer = 0;
		}
	}

	if (collider.onTheLeftWall || collider.onTheRightWall) {
		velocity.velocityY += kinematic.wallGravity * deltaTime;

		if (velocity.velocityY >= kinematic.maxWallSpeedY) {
			velocity.velocityY = kinematic.maxWallSpeedY;
		}
	} else {
		velocity.velocityY += kinematic.gravity * deltaTime;

		if (velocity.velocityY >= kinematic.maxSpeedY) {
			velocity.velocityY = kinematic.maxSpeedY;
		}
	}
}
