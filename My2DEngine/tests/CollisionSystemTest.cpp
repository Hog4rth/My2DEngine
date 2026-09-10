#include <vector>

#include <gtest/gtest.h>

#include "../CollisionSystem.h"
#include "../Components.h"

namespace Engine::Tests {

class CollisionSystemTest : public ::testing::Test {
protected:
	std::vector<TagComponent> tags;
	std::vector<PositionComponent> positions;
	std::vector<SizeComponent> sizes;
	std::vector<CollisionComponent> colliders;
	std::vector<VelocityComponent> velocities;

	void SetUp() override {
		tags.resize(4);
		positions.resize(4);
		sizes.resize(4);
		colliders.resize(4);
		velocities.resize(4);

		// Entità 0: Player
		tags[0].id = EntityTag::Player;
		sizes[0] = {10.0f, 10.0f};
		velocities[0].canItMove = true;

		// Entity 1: Solid
		tags[1].id = EntityTag::Solid;
		sizes[1] = {100.0f, 100.0f};
		colliders[1].isSolid = true;

		// Entity 2: Ignored (Tag none)
		tags[2].id = EntityTag::None;
		velocities[2].canItMove = true;

		// Entity 3: Ignored (can't move)
		tags[3].id = EntityTag::Player;
		velocities[3].canItMove = false;
	}

	void RunSystem(float deltaTime = 1.0f) {
		CollisionSystem::UpdateCollisions(tags, positions, sizes, colliders, velocities, deltaTime);
	}
};

TEST_F(CollisionSystemTest, IgnoreNoneAndImmovable) {
	RunSystem();
	EXPECT_FALSE(colliders[2].isOnTheGround);
	EXPECT_FALSE(colliders[3].isOnTheGround);
}

TEST_F(CollisionSystemTest, MoveRightCollision) {
	positions[0] = {0.0f, 0.0f};
	velocities[0] = {20.0f, 0.0f, true};
	positions[1] = {15.0f, 0.0f};

	RunSystem();

	EXPECT_TRUE(colliders[0].onTheRightWall);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, 5.0f);
}

TEST_F(CollisionSystemTest, MoveLeftCollision) {
	positions[0] = {20.0f, 0.0f};
	velocities[0] = {-20.0f, 0.0f, true};
	positions[1] = {-90.0f, 0.0f};

	RunSystem();

	EXPECT_TRUE(colliders[0].onTheLeftWall);
	EXPECT_FLOAT_EQ(velocities[0].velocityX, -10.0f);
}

TEST_F(CollisionSystemTest, MoveDownCollision) {
	positions[0] = {0.0f, 0.0f};
	velocities[0] = {0.0f, 20.0f, true};
	positions[1] = {0.0f, 15.0f};

	RunSystem();

	EXPECT_TRUE(colliders[0].isOnTheGround);
	EXPECT_FLOAT_EQ(velocities[0].velocityY, 5.0f);
}

TEST_F(CollisionSystemTest, MoveUpCollision) {
	positions[0] = {0.0f, 20.0f};
	velocities[0] = {0.0f, -20.0f, true};
	positions[1] = {0.0f, -90.0f};

	RunSystem();

	EXPECT_FLOAT_EQ(velocities[0].velocityY, -10.0f);
}

TEST_F(CollisionSystemTest, SensorLeftWall) {
	positions[0] = {10.0f, 0.0f};
	velocities[0] = {0.0f, 0.0f, true};
	positions[1] = {-90.0f, 0.0f};

	RunSystem();

	EXPECT_TRUE(colliders[0].onTheLeftWall);
}

TEST_F(CollisionSystemTest, SensorRightWall) {
	positions[0] = {0.0f, 0.0f};
	velocities[0] = {0.0f, 0.0f, true};
	positions[1] = {10.0f, 0.0f};

	RunSystem();

	EXPECT_TRUE(colliders[0].onTheRightWall);
}
}  // namespace Engine::Tests
