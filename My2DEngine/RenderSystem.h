#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "Components.h"
#include "FileManager.h"

class RenderSystem {
public:
	bool InitializeRenderer(FileManager& fileManager);
	void UpdateRender(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes);
	void Close();

private:
	int width = 800;
	int height = 600;
	std::string title = "My 2D Engine";

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{ nullptr, SDL_DestroyWindow };
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{ nullptr, SDL_DestroyRenderer };

	void RenderBackground();
	void RenderEntitiesByTag(const EntityTag targetTag, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a, std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes);

};
