#include <iostream>
#include "GameEngine.h"

bool GameEngine::Initialize() {

	userSettings.LoadFile();
	physicsSettings.LoadFile();

	InitializeComponents();

	if (!renderSystem.InitializeRenderer(userSettings)) return false;

	return true;
}

void GameEngine::Run() {

	gameIsGoing = true;
	lastTick = std::chrono::steady_clock::now();

	while (gameIsGoing) {

		UpdateDeltaTime();
		gameIsGoing = InputSystem::ProcessInput(tags, inputs);
		Update();
	}
}

void GameEngine::Close() {

	renderSystem.Close();
}

//--- Helpers ---

void GameEngine::InitializeComponents() {

	CreatePlayer(0, 300.0f, 300.0f, 50.0f, 50.0f);

	CreateSolid(1, 0.0f, 700.0f, 1024.0f, 68.0f); // The Floor
	CreateSolid(2, -10.0f, 0.0f, 50.0f, 768.0f); // The Left Wall (Map Border)
	CreateSolid(3, 984.0f, 0.0f, 50.0f, 768.0f); // The Right Wall (Map Border)
	CreateSolid(4, 400.0f, 600.0f, 50.0f, 100.0f); // The Low Obstacle
	CreateSolid(5, 550.0f, 500.0f, 200.0f, 40.0f); // The Suspended Lower Platform 
	CreateSolid(6, 550.0f, 250.0f, 200.0f, 40.0f); // The Suspended Higher Platform
}

void GameEngine::UpdateDeltaTime() {

	auto currentTick = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = currentTick - lastTick;
	deltaTime = elapsed.count();
	lastTick = currentTick;

	deltaTime = std::clamp(deltaTime, 0.0001f, 0.05f);
}

void GameEngine::Update() {

	PhysicsSystem::CalculateTrajectory(tags, inputs, colliders, velocities, kinematics, deltaTime);
	CollisionSystem::UpdateCollisions(tags, positions, sizes, colliders, velocities, deltaTime);
	MovementSystem::UpdatePosition(tags, positions, velocities, deltaTime);
	renderSystem.UpdateRender(tags, positions, sizes);
}

// --- Tag Functions --- **In the future the function will be removed and all the info will be stored in different .ini files (Player.ini, Solid.ini...)**

void GameEngine::CreatePlayer(const int entityID, const float positionX, const float positionY, const float width, const float height) {

	if (entityID < 0 || entityID >= MAX_ECS_ENTITIES) {
		std::cerr << "Error: Entity ID " << entityID << " is out of bounds!\n";
		return;
	}

	tags[entityID].id = EntityTag::Player;
	velocities[entityID].canItMove = true;
	positions[entityID].x = positionX;
	positions[entityID].y = positionY;
	sizes[entityID].width = width;
	sizes[entityID].height = height;

	kinematics[entityID].groundAcceleration = physicsSettings.Load<float>("GroundAcceleration", 3500.0f);
	kinematics[entityID].airAcceleration = physicsSettings.Load<float>("AirAcceleration", 2000.0f);
	kinematics[entityID].gravity = physicsSettings.Load<float>("Gravity", 2800.0f);
	kinematics[entityID].wallGravity = physicsSettings.Load<float>("WallGravity", 2000.0f);
	kinematics[entityID].maxSpeedX = physicsSettings.Load<float>("MaxSpeedX", 850.0f);
	kinematics[entityID].maxSpeedY = physicsSettings.Load<float>("MaxSpeedY", 3000.0f);
	kinematics[entityID].maxWallSpeedY = physicsSettings.Load<float>("MaxWallSpeedY", 1000.0f);
	kinematics[entityID].groundFriction = physicsSettings.Load<float>("GroundFriction", 10500.0f);
	kinematics[entityID].airFriction = physicsSettings.Load<float>("AirFriction", 1000.0f);
	kinematics[entityID].jumpForceX = physicsSettings.Load<float>("JumpForceX", 1600.0f);
	kinematics[entityID].jumpForceY = physicsSettings.Load<float>("JumpForceY", 1100.0f);
	kinematics[entityID].jumpBufferDuration = physicsSettings.Load<float>("JumpBufferDuration", 0.15f);
	kinematics[entityID].jumpCoyoteDuration = physicsSettings.Load<float>("JumpCoyoteDuration", 0.1f);
	kinematics[entityID].wallStickDuration = physicsSettings.Load<float>("WallStickDuration", 0.5f);

}

void GameEngine::CreateSolid(const int entityID, const float positionX, const float positionY, const float width, const float height) {

	if (entityID < 0 || entityID >= MAX_ECS_ENTITIES) {
		std::cerr << "Error: Entity ID " << entityID << " is out of bounds!\n";
		return;
	}

	tags[entityID].id = EntityTag::Solid;
	colliders[entityID].isSolid = true;
	positions[entityID].x = positionX;
	positions[entityID].y = positionY;
	sizes[entityID].width = width;
	sizes[entityID].height = height;

}
