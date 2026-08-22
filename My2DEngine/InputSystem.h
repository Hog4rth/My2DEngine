#pragma once
#include <SDL3/SDL.h>
#include "Components.h"

class InputSystem {
public:
	static bool ProcessInput(TagComponent tags[], InputComponent inputs[], const int MAX_ECS_ENTITIES);
};