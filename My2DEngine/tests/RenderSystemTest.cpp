// My2DEngine/tests/RenderSystemTest.cpp
#include <cstdio>

#include <fstream>
#include <vector>

#include <SDL3/SDL.h>
#include <gtest/gtest.h>

#include "../Components.h"
#include "../FileManager.h"
#include "../RenderSystem.h"

namespace Engine::Tests {

class RenderSystemTest : public ::testing::Test {
protected:
	void SetUp() override {
		std::ofstream out("test_render.ini");
		out << "Width=100\nHeight=100\n";
		out.close();
		// Uses "dummy" video driver to avoid setup errors since the tests are done in a headless environment (no windows)
		SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
	}

	void TearDown() override { std::remove("test_render.ini"); }
};

TEST_F(RenderSystemTest, FullRenderLifecycle) {
	FileManager fm("test_render.ini");
	fm.LoadFile();

	RenderSystem renderSystem;

	ASSERT_TRUE(renderSystem.InitializeRenderer(fm));

	std::vector<TagComponent> tags(3);
	std::vector<PositionComponent> positions(3);
	std::vector<SizeComponent> sizes(3);

	tags[0].id = EntityTag::Player;
	positions[0] = {10.0f, 10.0f};
	sizes[0] = {10.0f, 10.0f};

	tags[1].id = EntityTag::Solid;
	positions[1] = {0.0f, 20.0f};
	sizes[1] = {100.0f, 10.0f};

	tags[2].id = EntityTag::None;

	EXPECT_NO_THROW(renderSystem.UpdateRender(tags, positions, sizes));
	EXPECT_NO_THROW(renderSystem.Close());
}

}  // namespace Engine::Tests
