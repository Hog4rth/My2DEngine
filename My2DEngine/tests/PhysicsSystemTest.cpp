// My2DEngine/tests/PhysicsSystemTest.cpp
#include <vector>

#include <gtest/gtest.h>

#include "../Components.h"
#include "../PhysicsSystem.h"

namespace Engine::Tests {

class PhysicsSystemTest : public ::testing::Test {
protected:
	std::vector<TagComponent> tags;
	std::vector<InputComponent> inputs;
	std::vector<CollisionComponent> colliders;
	std::vector<VelocityComponent> velocities;
	std::vector<KinematicComponent> kinematics;

	void SetUp() override {
		tags.resize(1);
		inputs.resize(1);
		colliders.resize(1);
		velocities.resize(1);
		kinematics.resize(1);

		tags[0].id = EntityTag::Player;
		velocities[0].canItMove = true;

		kinematics[0].groundAcceleration = 100.0f;
		kinematics[0].airAcceleration = 50.0f;
		kinematics[0].gravity = 200.0f;
		kinematics[0].wallGravity = 100.0f;
		kinematics[0].maxSpeedX = 200.0f;
		kinematics[0].maxSpeedY = 300.0f;
		kinematics[0].maxWallSpeedY = 150.0f;
		kinematics[0].groundFriction = 50.0f;
		kinematics[0].airFriction = 20.0f;
		kinematics[0].jumpForceX = 150.0f;
		kinematics[0].jumpForceY = 250.0f;
		kinematics[0].jumpBufferDuration = 0.2f;
		kinematics[0].jumpCoyoteDuration = 0.1f;
		kinematics[0].wallStickDuration = 0.3f;
	}

	void RunSystem(float deltaTime) {
		PhysicsSystem::CalculateTrajectory(tags, inputs, colliders, velocities, kinematics, deltaTime);
	}
};

TEST_F(PhysicsSystemTest, IgnoreNoneAndImmovable) {
	tags.resize(2);
	inputs.resize(2);
	colliders.resize(2);
	velocities.resize(2);
	kinematics.resize(2);

	tags[0].id = EntityTag::None;
	velocities[0].canItMove = true;

	tags[1].id = EntityTag::Player;
	velocities[1].canItMove = false;

	RunSystem(0.1f);

	EXPECT_FLOAT_EQ(velocities[0].velocityY, 0.0f);
	EXPECT_FLOAT_EQ(velocities[1].velocityY, 0.0f);
}

TEST_F(PhysicsSystemTest, NonPlayerGravity) {
	tags[0].id = EntityTag::Enemy;
	velocities[0].velocityY = 290.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityY, 300.0f);
}

TEST_F(PhysicsSystemTest, PlayerFriction) {
	colliders[0].isOnTheGround = true;
	velocities[0].velocityX = 10.0f;
	inputs[0].direction = 0.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 5.0f);

	velocities[0].velocityX = -10.0f;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, -5.0f);
}

TEST_F(PhysicsSystemTest, PlayerGroundJump) {
	colliders[0].isOnTheGround = true;
	inputs[0].isJumping = true;
	inputs[0].wasJumping = false;

	RunSystem(0.1f);

	EXPECT_FLOAT_EQ(velocities[0].velocityY, -250.0f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpBufferTimer, 0.0f);
}

TEST_F(PhysicsSystemTest, PlayerLeftWallJump) {
	colliders[0].isOnTheGround = false;
	colliders[0].onTheLeftWall = true;
	inputs[0].isJumping = true;
	inputs[0].wasJumping = false;

	RunSystem(0.1f);

	EXPECT_FLOAT_EQ(velocities[0].velocityY, -250.0f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 150.0f);
}

TEST_F(PhysicsSystemTest, PlayerRightWallJump) {
	colliders[0].isOnTheGround = false;
	colliders[0].onTheRightWall = true;
	inputs[0].isJumping = true;
	inputs[0].wasJumping = false;

	RunSystem(0.1f);

	EXPECT_FLOAT_EQ(velocities[0].velocityY, -250.0f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, -150.0f);
}

TEST_F(PhysicsSystemTest, PlayerWallStick) {
	colliders[0].isOnTheGround = false;
	colliders[0].onTheLeftWall = true;
	inputs[0].direction = 0.0f;

	RunSystem(0.1f);

	EXPECT_FLOAT_EQ(kinematics[0].wallStickTimer, 0.3f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 0.0f);
}

TEST_F(PhysicsSystemTest, PlayerGravity) {
	colliders[0].isOnTheGround = false;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityY, 20.0f);

	colliders[0].onTheLeftWall = true;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityY, 30.0f);
}

TEST_F(PhysicsSystemTest, PlayerFrictionClamping) {
	colliders[0].isOnTheGround = true;
	velocities[0].velocityX = 2.0f;
	inputs[0].direction = 0.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 0.0f);

	velocities[0].velocityX = -2.0f;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 0.0f);
}

TEST_F(PhysicsSystemTest, PlayerOppositeInputFriction) {
	colliders[0].isOnTheGround = true;
	velocities[0].velocityX = 30.0f;
	inputs[0].direction = -1.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 15.0f);
}

TEST_F(PhysicsSystemTest, PlayerJumpBufferAndCoyote) {
	colliders[0].isOnTheGround = true;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpCoyoteTimer, 0.1f);

	colliders[0].isOnTheGround = false;
	RunSystem(0.05f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpCoyoteTimer, 0.05f);

	inputs[0].isJumping = true;
	inputs[0].wasJumping = false;
	RunSystem(0.01f);

	EXPECT_FLOAT_EQ(velocities[0].velocityY, -250.0f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpBufferTimer, 0.0f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpCoyoteTimer, 0.0f);
}

TEST_F(PhysicsSystemTest, VelocityClamping) {
	colliders[0].isOnTheGround = true;
	velocities[0].velocityX = 195.0f;
	inputs[0].direction = 1.0f;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 200.0f);

	colliders[0].isOnTheGround = false;
	velocities[0].velocityY = 290.0f;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityY, 300.0f);

	colliders[0].onTheLeftWall = true;
	velocities[0].velocityY = 145.0f;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityY, 150.0f);
}

TEST_F(PhysicsSystemTest, WallStickTimerDecrease) {
	colliders[0].isOnTheGround = false;
	colliders[0].onTheLeftWall = true;
	inputs[0].direction = 0.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(kinematics[0].wallStickTimer, 0.3f);

	colliders[0].onTheLeftWall = false;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(kinematics[0].wallStickTimer, 0.2f);

	RunSystem(0.25f);
	EXPECT_FLOAT_EQ(kinematics[0].wallStickTimer, 0.0f);
}

TEST_F(PhysicsSystemTest, JumpBufferTimerDecrease) {
	inputs[0].isJumping = true;
	inputs[0].wasJumping = false;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpBufferTimer, 0.2f);

	inputs[0].isJumping = false;
	inputs[0].wasJumping = true;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(kinematics[0].jumpBufferTimer, 0.1f);
}

TEST_F(PhysicsSystemTest, FrictionPointingRight) {
	colliders[0].isOnTheGround = true;
	velocities[0].velocityX = -30.0f;
	inputs[0].direction = 1.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, -15.0f);
}

TEST_F(PhysicsSystemTest, WallStickPreventsHorizontalMovement) {
	colliders[0].isOnTheGround = false;
	colliders[0].onTheRightWall = true;
	inputs[0].direction = 0.0f;

	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(kinematics[0].wallStickTimer, 0.3f);

	inputs[0].direction = -1.0f;
	RunSystem(0.1f);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 0.0f);
}
}  // namespace Engine::Tests
