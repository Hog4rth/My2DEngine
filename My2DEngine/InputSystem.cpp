#include <iostream>
#include "InputSystem.h"

bool InputSystem::ProcessInput(std::span<const TagComponent> tags, std::span<InputComponent> inputs) {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_EVENT_QUIT) { // Handle quit event
			return false;
		}
	}

	const bool* state = SDL_GetKeyboardState(nullptr);

	float currentDirectionX = (float)state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A]; // Calculate direction based on key states
	bool isJumpKeyPressed = (bool)state[SDL_SCANCODE_SPACE];

	for (size_t i = 0; i < tags.size(); ++i) {

		if (tags[i].id != EntityTag::Player) {
			continue;
		}

		inputs[i].direction = currentDirectionX;

		inputs[i].wasJumping = inputs[i].isJumping;
		inputs[i].isJumping = isJumpKeyPressed;
		break;
	}
	return true;
}
