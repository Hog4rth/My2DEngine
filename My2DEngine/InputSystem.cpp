#include <iostream>
#include "InputSystem.h"

bool InputSystem::ProcessInput(TagComponent tags[], InputComponent inputs[], const int MAX_ECS_ENTITIES) {
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT) { // Handle quit event
            return false;
        }
    }

    const bool* state = SDL_GetKeyboardState(nullptr);

    float currentDirectionX = (float)state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A]; // Calculate direction based on key states
    bool currentDirectionY = (bool)state[SDL_SCANCODE_SPACE];

    for (int i = 0; i < MAX_ECS_ENTITIES; ++i) {

        if (tags[i].id != EntityTag::Player) {
            continue;
        }
            
        inputs[i].direction = currentDirectionX;
            
        inputs[i].wasJumping = inputs[i].isJumping;
        inputs[i].isJumping = currentDirectionY;
        break;
    }
    return true;
}