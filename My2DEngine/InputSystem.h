#pragma once
#include "Components.h"

class InputSystem {
public:
	static bool ProcessInput(std::span<const TagComponent> tags, std::span<InputComponent> inputs);
};
