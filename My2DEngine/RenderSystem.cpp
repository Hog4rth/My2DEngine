#include "RenderSystem.h"

#include <iostream>

#include "Components.h"

bool RenderSystem::InitializeRenderer(FileManager& fileManager) {
	width = fileManager.Load<int>("Width", width);
	height = fileManager.Load<int>("Height", height);

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Error, SDL_Init: " << SDL_GetError() << "\n";
		return false;
	}

	window.reset(SDL_CreateWindow(title.c_str(), width, height, 0));
	if (window == nullptr) {
		std::cerr << "Error CreateWindow: " << SDL_GetError() << "\n";
		SDL_Quit();
		return false;
	}

	renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
	if (renderer == nullptr) {
		std::cerr << "Error CreateRenderer: " << SDL_GetError() << "\n";
		window.reset();
		SDL_Quit();
		return false;
	}
	return true;
}

void RenderSystem::UpdateRender(std::span<const TagComponent> tags, std::span<const PositionComponent> positions,
                                std::span<const SizeComponent> sizes) {
	RenderBackground();
	RenderEntitiesByTag(EntityTag::Solid, 0, 255, 0, 255, tags, positions, sizes);
	RenderEntitiesByTag(EntityTag::Player, 255, 0, 0, 255, tags, positions, sizes);

	SDL_RenderPresent(renderer.get());
}

void RenderSystem::Close() {
	renderer.reset();
	window.reset();
	SDL_Quit();
}

//---Helpers---

void RenderSystem::RenderBackground() {
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);  // Black background
	SDL_RenderClear(renderer.get());
}

void RenderSystem::RenderEntitiesByTag(const EntityTag targetTag, const Uint8 r, const Uint8 g, const Uint8 b,
                                       const Uint8 a, std::span<const TagComponent> tags,
                                       std::span<const PositionComponent> positions,
                                       std::span<const SizeComponent> sizes) {
	SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);

	for (size_t i = 0; i < tags.size(); ++i) {
		if (tags[i].id != targetTag)
			continue;

		SDL_FRect rect = {positions[i].x, positions[i].y, sizes[i].width, sizes[i].height};
		SDL_RenderFillRect(renderer.get(), &rect);
	}
}
