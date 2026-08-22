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
	void RenderMC(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes);
	void RenderSolids(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes);

public:
	bool InitializeRenderer(FileManager& fileManager);
	void UpdateRender(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes);
	void Close();

};
