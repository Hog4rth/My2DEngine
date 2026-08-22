#pragma once
#include <string>
#include "Components.h"
#include "MovementSystem.h"
#include "FileManager.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"

class GameEngine {
public:
	bool Initialize();
	void Run();
	void Close();

private:

	static constexpr int MAX_ECS_ENTITIES = 7;

	// FILE NAMES
	FileManager fileManager;
	RenderSystem renderSystem;
	InputSystem inputSystem;

	// DELTA TIME
	Uint64 lastTick = 0;
	float deltaTime = 0.0f;

	// COMPONENTS
	TagComponent tags[MAX_ECS_ENTITIES];
	PositionComponent positions[MAX_ECS_ENTITIES];
	SizeComponent sizes[MAX_ECS_ENTITIES];
	CollisionComponent colliders[MAX_ECS_ENTITIES];
	InputComponent inputs[MAX_ECS_ENTITIES];
	VelocityComponent velocities[MAX_ECS_ENTITIES];
	KinematicComponent kinematics[MAX_ECS_ENTITIES];

	// GAME LOOP
	bool gameIsGoing = false;

	void CreatePlayer(int entityID, float positionX, float positionY, float width, float height);
	void CreateSolid(int entityID, float positionX, float positionY, float width, float height);

	void InitializeComponents();
	void UpdateDeltaTime();
	void Update();
	
};