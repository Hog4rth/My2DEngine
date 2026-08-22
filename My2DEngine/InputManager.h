#pragma once
#include <SDL3/SDL.h>
#include "Components.h"

class InputManager {
private:
	SDL_Event event;

public:
	bool ProcessInput(TagComponent tags[], InputComponent inputs[], const int MAX_ECS_ENTITIES);
};