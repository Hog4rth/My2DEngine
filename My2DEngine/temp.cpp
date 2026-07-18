#include <iostream>
#include <fstream>  // <--- NECESSARIO PER LEGGERE I FILE ESTERNI!
#include <string>
#include "GameEngine.h"

bool GameEngine::Initialize(const std::string& percorsoFileConfig) {

    // 1. Creiamo l'oggetto per le impostazioni e proviamo ad aprire il file
    GameSettings impostazioni;
    std::ifstream file(percorsoFileConfig);

    if (file.is_open()) {
        std::cout << "SISTEMA: Caricamento impostazioni da file '" << percorsoFileConfig << "'..." << std::endl;
        std::string riga;

        // Leggiamo il file riga per riga fino alla fine
        while (std::getline(file, riga)) {
            // Troviamo dove si trova il simbolo '='
            size_t posizioneUguale = riga.find('=');

            if (posizioneUguale != std::string::npos) {
                // Separiamo la parola a sinistra (chiave) da quella a destra (valore)
                std::string chiave = riga.substr(0, posizioneUguale);
                std::string valore = riga.substr(posizioneUguale + 1);

                // Assegniamo i dati! (std::stoi trasforma una stringa di testo in un numero INT)
                if (chiave == "Titolo")    impostazioni.titolo = valore;
                else if (chiave == "Larghezza") impostazioni.larghezza = std::stoi(valore);
                else if (chiave == "Altezza")   impostazioni.altezza = std::stoi(valore);
            }
        }
        file.close();
    }
    else {
        std::cout << "ATTENZIONE: File config non trovato! Uso impostazioni di default." << std::endl;
    }

    // --- DA QUI IN POI È IL TUO CODICE DI SDL, MA USA I DATI DEL FILE! ---

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

    // Guarda che eleganza: usiamo i dati caricati dall'esterno!
    window = SDL_CreateWindow(impostazioni.titolo.c_str(), impostazioni.larghezza, impostazioni.altezza, 0);

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