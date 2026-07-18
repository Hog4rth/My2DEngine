#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "GameEngine.h"



bool GameEngine::Inizialize(const std::string& FileConfigPath) {

	// I take the settings from the file, if it exists, otherwise I use the default settings
    GameSettings settings;
    std::ifstream file(FileConfigPath);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            size_t equalPosition = line.find('=');

            if (equalPosition != std::string::npos) {
                std::string key = line.substr(0, equalPosition);
                std::string value = line.substr(equalPosition + 1);

                if (key == "Title")            settings.title = value;
                else if (key == "Width")       settings.width = std::stoi(value);
                else if (key == "Height")      settings.height = std::stoi(value);
            }
        }
        file.close();
    
    } else {
        std::cout << "WARNING: File config not found! I'm using default settings." << std::endl;
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
    GameIsGoing = true;
    
    while (GameIsGoing) {
        GameIsGoing = IsGameGoing();

        // --- Draw The Background ---
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // --- Draw The Protagonist ---
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &Hogarth);

        SDL_RenderPresent(renderer);
    }
}

void GameEngine::Close() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

bool GameEngine::IsGameGoing() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) { // The user has closed the window from the X in the top right
            return false;
        }
    }
    return true;
}