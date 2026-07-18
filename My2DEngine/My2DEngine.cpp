#include <iostream>
#include "GameEngine.h"

int main(int argc, char* argv[]) {
    std::cout << "Starting the program..." << std::endl;

    GameEngine engine;

    if (!engine.Inizialize("Settings.ini")) {
        std::cout << "GPU can't start up" << std::endl;
        return -1;
    }

    engine.Run();
    engine.Close();

    std::cout << "Task Completed with success!" << std::endl;
    return 0;

}