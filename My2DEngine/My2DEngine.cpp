#include <iostream>
#include "GameEngine.h"

int main(int argc, char* argv[]) {
    std::cout << "Starting the program..." << std::endl;

    // 1. Creiamo il nostro motore (L'oggetto OOP centrale)
    GameEngine engine;

    // 2. Lo accendiamo (Qui dentro creerà la finestra, il pittore e SDL)
    if (!engine.Inizialize("Titolo", 800, 600)) {
        std::cout << "GPU can't start up" << std::endl;
        return -1;
    }

    // 3. Facciamo partire il battito cardiaco (Il Game Loop infinito)
    engine.Run();

    // 4. Quando il giocatore esce dal ciclo Run(), spegniamo tutto pulito
    engine.Close();

    std::cout << "Task Completed with success!" << std::endl;
    return 0;

}