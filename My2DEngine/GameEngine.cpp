#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "GameEngine.h"

bool GameEngine::Inizialize(const std::string& FileConfigPath) {

	// I take the settings from the config file, if it exists, otherwise I use the default settings
    GameSettings settings;
    std::ifstream file(FileConfigPath);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            size_t equalPosition = line.find('=');

            if (equalPosition != std::string::npos) {
                std::string key = line.substr(0, equalPosition);
                std::string value = line.substr(++equalPosition);

                if (key == "Title")            settings.title = value;
                else if (key == "Width")       settings.width = std::stoi(value);
                else if (key == "Height")      settings.height = std::stoi(value);
				else if (key == "PositionX")    Position[0].x = std::stof(value);
				else if (key == "PositionY")    Position[0].y = std::stof(value);
            }
        }
        file.close();
    
    } else {
        std::cout << "Warning: Config file not found! Using default settings." << std::endl;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Error, SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(settings.title.c_str(), settings.width, settings.height, 0);
    if (window == nullptr) {
        std::cout << "Error CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cout << "Error CreateRenderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return true;
}

void GameEngine::Run() {
    
    lastTick = SDL_GetTicks();
    
    GameIsGoing = true;

    while (GameIsGoing) {

        Uint64 currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        // --- Delta Time Clamping ---
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f; // 20 FPS
        }

        ProcessInput(); // Process input and check if the game should continue
        Update(deltaTime);
        Render();
    }
}

void GameEngine::Close() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void GameEngine::ProcessInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) { // Handle quit event
            GameIsGoing = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_A) {
                Velocity[0].vx = -100.0f; // Move left
            }
            else if (event.key.key == SDLK_D) {
                Velocity[0].vx = 100.0f; // Move right
            }
        }
        else if (event.type == SDL_EVENT_KEY_UP) {
            if (event.key.key == SDLK_A || event.key.key == SDLK_D) {
                Velocity[0].vx = 0.0f; // Stop horizontal movement
            }
        }
    }
}

void GameEngine::Update(float deltaTime) {

	MovementSystem::Update(Position, Velocity, 1, deltaTime); // Ci andrebbe MAX_ECS_ENTITIES ma per ora lo metto a 1 per far muovere solo il personaggio
}

void GameEngine::Render() {

    // --- Draw the background ---
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // --- Update Main Character position ---
    Hogarth.x = Position[0].x;
    Hogarth.y = Position[0].y;

    // --- Draw the protagonist ---
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &Hogarth);

    SDL_RenderPresent(renderer);
}