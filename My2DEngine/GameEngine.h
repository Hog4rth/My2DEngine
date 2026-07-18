#pragma once
#include <SDL3/SDL.h>
#include <string> 

// Questa è la struttura che contiene le impostazioni (Con valori di sicurezza di default!)
struct GameSettings {
	std::string title = "Engine di Default";
	int width = 800;
	int height = 600;
};

class GameEngine {
public:
	bool Inizialize(const std::string& percorsoFileConfig);
	void Run();
	void Close();

private:
	bool IsGameGoing();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool GameIsGoing = false;

	SDL_FRect mc = { 100.0f, 100.0f, 50.0f, 50.0f }; // Main Character

};