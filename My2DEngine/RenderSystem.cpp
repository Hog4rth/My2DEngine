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

	window = SDL_CreateWindow(title.c_str(), width, height, 0);
	if (window == nullptr) {
		std::cerr << "Error CreateWindow: " << SDL_GetError() << "\n";
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, nullptr);
	if (renderer == nullptr) {
		std::cerr << "Error CreateRenderer: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	return true;
}

void RenderSystem::UpdateRender(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], const int MAX_ECS_ENTITIES) {

	RenderBackground();
	RenderSolids(tags, positions, sizes, MAX_ECS_ENTITIES);
	RenderMC(tags, positions, sizes, MAX_ECS_ENTITIES);

	SDL_RenderPresent(renderer);
}

void RenderSystem::Close() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//---Helpers---

void RenderSystem::RenderBackground() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
	SDL_RenderClear(renderer);
}

void RenderSystem::RenderMC(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], const int MAX_ECS_ENTITIES) {

	for (int i = 0; i < MAX_ECS_ENTITIES; ++i) {

		if (tags[i].id != EntityTag::Player) {
			continue;
		}
		SDL_FRect Hogarth = { positions[i].x, positions[i].y, sizes[i].width, sizes[i].height }; // Main Character
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for the MC
		SDL_RenderFillRect(renderer, &Hogarth);
		break;
	}
}

void RenderSystem::RenderSolids(const TagComponent tags[], const PositionComponent positions[], const SizeComponent sizes[], const int MAX_ECS_ENTITIES) {

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for solids

	for (int i = 0; i < MAX_ECS_ENTITIES; ++i) {

		if (tags[i].id != EntityTag::Solid) {
			continue;
		}

		SDL_FRect solid = { positions[i].x, positions[i].y, sizes[i].width, sizes[i].height };
		SDL_RenderFillRect(renderer, &solid);
	}
}
