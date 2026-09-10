#include <vector>

#include <SDL3/SDL.h>
#include <gtest/gtest.h>

#include "../Components.h"
#include "../InputSystem.h"

namespace Engine::Tests {

class InputSystemTest : public ::testing::Test {
protected:
	std::vector<TagComponent> tags;
	std::vector<InputComponent> inputs;

	void SetUp() override {
		SDL_Init(SDL_INIT_EVENTS);

		tags.resize(3);
		inputs.resize(3);

		// Entity 0: Ignored (Tag None)
		tags[0].id = EntityTag::None;

		// Entity 1: Player (is pressing jump key)
		tags[1].id = EntityTag::Player;
		inputs[1].isJumping = true;

		// Entità 2: Second Player (should not be processed)
		tags[2].id = EntityTag::Player;
	}

	void TearDown() override { SDL_Quit(); }
};

TEST_F(InputSystemTest, ProcessInput_NoQuitEvent_UpdatesPlayerInput) {
	// Empty the event queue before each test to avoid false positives from previous runs
	SDL_PumpEvents();
	SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);

	bool result = InputSystem::ProcessInput(tags, inputs);

	EXPECT_TRUE(result);

	EXPECT_FLOAT_EQ(inputs[1].direction, 0.0f);
	EXPECT_TRUE(inputs[1].wasJumping);
	EXPECT_FALSE(inputs[1].isJumping);

	EXPECT_FALSE(inputs[2].wasJumping);
}

TEST_F(InputSystemTest, ProcessInput_QuitEvent) {
	SDL_Event quitEvent{};
	quitEvent.type = SDL_EVENT_QUIT;
	SDL_PushEvent(&quitEvent);

	bool result = InputSystem::ProcessInput(tags, inputs);

	EXPECT_FALSE(result);
}
}  // namespace Engine::Tests
