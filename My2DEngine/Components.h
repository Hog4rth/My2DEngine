#pragma once
#include <span>

enum class EntityTag {
	Player,
	Solid,
	Enemy,
	None
};

struct TagComponent {
	EntityTag id = EntityTag::None;
};

struct PositionComponent {
	float x = 0.0f;
	float y = 0.0f;
};

struct SizeComponent {
	float width = 0.0f;
	float height = 0.0f;
};

struct CollisionComponent {
	bool onTheLeftWall = false;
	bool onTheRightWall = false;
	bool isSolid = false;
	bool isOnTheGround = false;
};

struct InputComponent {
	float direction = 0.0f;

	bool wasJumping = false;
	bool isJumping = false;
};

struct VelocityComponent {
	float velocityX = 0.0f;
	float velocityY = 0.0f;

	bool canItMove = false;
};

struct KinematicComponent {
	float acceleration = 0.0f;
	float gravity = 0.0f;
	float maxSpeed = 0.0f;
	float friction = 0.0f;
	float jumpForceY = 0.0f;
	float jumpForceX = 0.0f;

	float jumpBufferTimer = 0.0f;
	float jumpBufferDuration = 0.15f; // 0.15 seconds
	float jumpCoyoteTimer = 0.0f;
	float jumpCoyoteDuration = 0.1f; // 0.1 seconds
};
