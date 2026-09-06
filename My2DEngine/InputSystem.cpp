#include "InputSystem.h"

#include <SDL3/SDL.h>

bool InputSystem::ProcessInput(std::span<const TagComponent> tags, std::span<InputComponent> inputs) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			return false;  // Handle quit event
	}

	const bool* state = SDL_GetKeyboardState(nullptr);

	// Calculate direction based on key states
	float currentDirectionX = static_cast<float>(state[SDL_SCANCODE_D]) - static_cast<float>(state[SDL_SCANCODE_A]);
	bool isJumpKeyPressed = state[SDL_SCANCODE_SPACE];

	for (size_t i = 0; i < tags.size(); ++i) {
		if (tags[i].id != EntityTag::Player)
			continue;

		inputs[i].direction = currentDirectionX;

		inputs[i].wasJumping = inputs[i].isJumping;
		inputs[i].isJumping = isJumpKeyPressed;
		break;
	}
	return true;
}
