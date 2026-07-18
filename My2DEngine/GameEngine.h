#pragma once
#include <SDL3/SDL.h>
#include <string> 

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
	bool IsGameGoing();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool GameIsGoing = false;

	SDL_FRect Hogarth = { 100.0f, 100.0f, 50.0f, 50.0f }; // Main Character

};