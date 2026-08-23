#include <iostream>
#include "Components.h"
#include "RenderSystem.h"

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
		SDL_Quit();
		return false;
	}
	return true;
}

void RenderSystem::UpdateRender(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes) {

	RenderBackground();
	RenderSolids(tags, positions, sizes);
	RenderMC(tags, positions, sizes);

	SDL_RenderPresent(renderer.get());
}

void RenderSystem::Close() {

	SDL_Quit();
}

//---Helpers---

void RenderSystem::RenderBackground() {
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255); // Black background
	SDL_RenderClear(renderer.get());
}

void RenderSystem::RenderMC(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes) {

	for (size_t i = 0; i < tags.size(); ++i) {

		if (tags[i].id != EntityTag::Player) {
			continue;
		}
		SDL_FRect Hogarth = { positions[i].x, positions[i].y, sizes[i].width, sizes[i].height }; // Main Character
		SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255); // Red color for the MC
		SDL_RenderFillRect(renderer.get(), &Hogarth);
		break;
	}
}

void RenderSystem::RenderSolids(std::span<const TagComponent> tags, std::span<const PositionComponent> positions, std::span<const SizeComponent> sizes) {

	SDL_SetRenderDrawColor(renderer.get(), 0, 255, 0, 255); // Green color for solids

	for (size_t i = 0; i < tags.size(); ++i) {

		if (tags[i].id != EntityTag::Solid) {
			continue;
		}

		SDL_FRect solid = { positions[i].x, positions[i].y, sizes[i].width, sizes[i].height };
		SDL_RenderFillRect(renderer.get(), &solid);
	}
}
