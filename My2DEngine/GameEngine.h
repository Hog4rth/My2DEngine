#pragma once
#include <SDL3/SDL.h>

class GameEngine {
public:
	bool Inizialize(const char* title, int width, int height);
	void Run();
	void Close();

private:
	bool IsGameGoing();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool GameIsGoing = false;

	SDL_FRect mc = { 100.0f, 100.0f, 50.0f, 50.0f }; // Main Character

};