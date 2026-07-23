#pragma once
#include <SDL3/SDL.h>
#include <string> 
#include "Components.h"
#include "MovementSystem.h"
#define MAX_ECS_ENTITIES 100

struct GameSettings {
	std::string title = "Engine Default";
	int width = 800;
	int height = 600;
};

class GameEngine {
public:
	bool Inizialize(const std::string& FileConfigPath);
	void Run();
	void Close();

private:
	// DELTA TIME
	Uint64 lastTick = 0;
	float deltaTime = 0.0f;

	// COMPONENTS
	PositionComponent Position[MAX_ECS_ENTITIES];
	VelocityComponent Velocity[MAX_ECS_ENTITIES];
	SDL_FRect mc = { 100.0f, 100.0f, 50.0f, 50.0f }; // Main Character

	// GAME LOOP
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool GameIsGoing = false;

	void ProcessInput();
	void Update(float deltaTime);
	void Render();
	
};