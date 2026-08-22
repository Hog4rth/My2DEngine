#pragma once
#include <SDL3/SDL.h>
#include "Components.h"
#include "FileManager.h"

class RenderSystem {
private:
	int width = 800;
	int height = 600;
	std::string title = "My 2D Engine";

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	void RenderBackground();
	void RenderMC(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], const int MAX_ECS_ENTITIES);
	void RenderSolids(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], const int MAX_ECS_ENTITIES);

public:
	bool InitializeRenderer(FileManager& fileManager);
	void UpdateRender(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], const int MAX_ECS_ENTITIES);
	void Close();

};
