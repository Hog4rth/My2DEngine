#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "GameEngine.h"



bool GameEngine::Inizialize(const std::string& percorsoFileConfig) {

	// Prendo le impostazioni dal file di configurazione
    GameSettings settings;
    std::ifstream file(percorsoFileConfig);

    // Stampiamo esattamente in quale cartella il PC sta cercando il file!
    std::cout << "DEBUG: Il gioco sta cercando nella cartella: "
        << std::filesystem::current_path() << std::endl;

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            size_t equalPosition = line.find('=');

            if (equalPosition != std::string::npos) {
                std::string key = line.substr(0, equalPosition);
                std::string value = line.substr(equalPosition + 1);

                if (key == "Titolo")            settings.title = value;
                else if (key == "Larghezza")    settings.width = std::stoi(value);
                else if (key == "Altezza")      settings.height = std::stoi(value);
            }
        }
        file.close();
    
    } else {
        std::cout << "ATTENZIONE: File config non trovato! Uso settings di default." << std::endl;
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

        // --- DISEGNA LO SFONDO ---
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // --- DISEGNA IL PROTAGONISTA ---
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &mc);

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
        if (event.type == SDL_EVENT_QUIT) { // L'utente ha chiuso la finestra dalla X in alto a destra
            return false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_SPACE) { // L'utente ha chiuso la finestra premendo spazio
                return false;
            }
        }
    }
    return true;
}