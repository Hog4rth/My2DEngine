#include <cstdio>

#include <fstream>

#include <SDL3/SDL.h>
#include <gtest/gtest.h>

#include "../GameEngine.h"

namespace Engine::Tests {

class GameEngineTest : public ::testing::Test {
protected:
	void SetUp() override {
		SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");

		std::ofstream settings("Settings.ini");
		settings << "Width=800\nHeight=600\n";
		settings.close();

		std::ofstream physics("Physics.ini");
		physics << "Gravity=2800.0\n";
		physics.close();
	}

	void TearDown() override {
		std::remove("Settings.ini");
		std::remove("Physics.ini");
	}
};

TEST_F(GameEngineTest, FullEngineLifecycle) {
	GameEngine engine;

	ASSERT_TRUE(engine.Initialize());

	// Inject a quit event to exit the game loop immediately
	SDL_Event quitEvent{};
	quitEvent.type = SDL_EVENT_QUIT;
	SDL_PushEvent(&quitEvent);

	EXPECT_NO_THROW(engine.Run());
	EXPECT_NO_THROW(engine.Close());
}
}  // namespace Engine::Tests
