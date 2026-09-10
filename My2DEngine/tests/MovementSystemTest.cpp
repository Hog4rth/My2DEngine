#include <vector>

#include <gtest/gtest.h>

#include "../Components.h"
#include "../MovementSystem.h"

namespace Engine::Tests {

class MovementSystemTest : public ::testing::Test {
protected:
	std::vector<TagComponent> tags;
	std::vector<PositionComponent> positions;
	std::vector<VelocityComponent> velocities;

	void SetUp() override {
		tags.resize(3);
		positions.resize(3);
		velocities.resize(3);

		// Entity 0: Player
		tags[0].id = EntityTag::Player;
		positions[0] = {10.0f, 20.0f};
		velocities[0] = {5.0f, -2.0f, true};

		// Entity 1: Ignored (Tag none)
		tags[1].id = EntityTag::None;
		positions[1] = {0.0f, 0.0f};
		velocities[1] = {10.0f, 10.0f, true};

		// Entity 2: Ignored (can't move)
		tags[2].id = EntityTag::Enemy;
		positions[2] = {100.0f, 100.0f};
		velocities[2] = {50.0f, 50.0f, false};
	}
};

TEST_F(MovementSystemTest, UpdatePosition_AppliesVelocityCorrectly) {
	const float deltaTime = 2.0f;
	MovementSystem::UpdatePosition(tags, positions, velocities, deltaTime);

	EXPECT_FLOAT_EQ(positions[0].x, 20.0f);
	EXPECT_FLOAT_EQ(positions[0].y, 16.0f);

	EXPECT_FLOAT_EQ(positions[1].x, 0.0f);
	EXPECT_FLOAT_EQ(positions[1].y, 0.0f);

	EXPECT_FLOAT_EQ(positions[2].x, 100.0f);
	EXPECT_FLOAT_EQ(positions[2].y, 100.0f);
}
}  // namespace Engine::Tests
