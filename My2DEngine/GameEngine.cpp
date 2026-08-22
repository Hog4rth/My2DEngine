#include <string>
#include "GameEngine.h"

bool GameEngine::Initialize() {

    InitializeComponents();

    fileManager.LoadDefaultSettings();

    if (!renderSystem.InitializeRenderer(&fileManager)) {
        return false;
    }
    return true;
}

void GameEngine::Run() {

    lastTick = SDL_GetTicks();
    gameIsGoing = true;

    while (gameIsGoing) {

        UpdateDeltaTime();
        gameIsGoing = inputManager.ProcessInput(tags, colliders, inputs, MAX_ECS_ENTITIES);
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

	Uint64 currentTick = SDL_GetTicks();
	deltaTime = (currentTick - lastTick) / 1000.0f;
	lastTick = currentTick;

	// Delta Time Clamping
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f; // 20 FPS
	}
}

void GameEngine::Update() {

	PhysicsSystem::CalculateTrajectory(tags, inputs, colliders, velocities, kinematics, deltaTime, MAX_ECS_ENTITIES);
	CollisionSystem::UpdateCollisions(tags, positions, sizes, colliders, velocities, deltaTime, MAX_ECS_ENTITIES);
	MovementSystem::UpdatePosition(tags, positions, velocities, deltaTime, MAX_ECS_ENTITIES);
    renderSystem.UpdateRender(tags, positions, sizes, MAX_ECS_ENTITIES);
}

// --- Tag Functions ---

void GameEngine::CreatePlayer(int entityID, float PositionX, float PositionY, float width, float height) {

    tags[entityID].id = EntityTag::Player;
    velocities[entityID].canItMove = true;
    positions[entityID].x = PositionX;
    positions[entityID].y = PositionY;
    sizes[entityID].width = width;
    sizes[entityID].height = height;
}

void GameEngine::CreateSolid(int entityID, float PositionX, float PositionY, float width, float height) {

    tags[entityID].id = EntityTag::Solid;
    colliders[entityID].isSolid = true;
    positions[entityID].x = PositionX;
    positions[entityID].y = PositionY;
    sizes[entityID].width = width;
    sizes[entityID].height = height;

}