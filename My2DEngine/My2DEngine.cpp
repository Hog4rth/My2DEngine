#include <iostream>
#include "GameEngine.h"

int main(int argc, char* argv[]) {
	std::cout << "Starting the program...\n";

	GameEngine engine;

	if (!engine.Initialize()) {
		std::cerr << "Engine failed to initialize\n";
		return -1;
	}

	engine.Run();
	engine.Close();

	std::cout << "Task Completed with success!\n";
	return 0;

}
