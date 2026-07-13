#include <iostream>
#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
    // 1. Inizializziamo il sottosistema video di SDL3
    // In SDL3 le funzioni di inizializzazione restituiscono true (vero) se va tutto bene!
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Errore critico SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "Motore grafico SDL3 inizializzato con successo!" << std::endl;

    // 2. Creiamo la nostra prima finestra di gioco (800x600 pixel)
    // Nota quanto è pulita la nuova sintassi di SDL 3 rispetto al passato!
    SDL_Window* finestra = SDL_CreateWindow("Il mio primo Engine 2D - SDL 3.4", 800, 600, 0);

    if (finestra == nullptr) {
        std::cout << "Errore creazione finestra: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    std::cout << "Finestra creata! Il gioco restera' aperto per 3 secondi..." << std::endl;

    // 3. Mettiamo il programma in pausa per 3 secondi (3000 millisecondi)
    // Questo ci permette di ammirare la finestra prima che il codice arrivi alla fine!
    SDL_Delay(3000);

    // 4. Pulizia finale: chiudiamo la finestra e spegniamo SDL
    SDL_DestroyWindow(finestra);
    SDL_Quit();

    std::cout << "Chiusura pulita del motore completata." << std::endl;
    return 0;
}