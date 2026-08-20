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
	SDL_FRect Hogarth = { 300.0f, 300.0f, 50.0f, 50.0f}; // Main Character
	SDL_FRect solid = { 0.0f, 0.0f, 50.0f, 50.0f };

	void RenderBackground();
	void RenderMC(TagComponent tags[], PositionComponent positions[], const int MAX_ECS_ENTITIES);
	void RenderSolids(TagComponent tags[], PositionComponent positions[], SizeComponent sizes[], const int MAX_ECS_ENTITIES);
	
public:
	bool InitializeRenderer(FileManager* fileManager);
	void UpdateRender(TagComponent tags[], PositionComponent positions[], SizeComponent sizes[], const int MAX_ECS_ENTITIES);
	void Close();

};