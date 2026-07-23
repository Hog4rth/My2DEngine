#include "MovementSystem.h"

void MovementSystem::Update(PositionComponent positions[], VelocityComponent velocities[], int maxEntities, float deltaTime) {
    for (int i = 0; i < maxEntities; ++i) {
        
        positions[i].x += velocities[i].vx * deltaTime;
        positions[i].y += velocities[i].vy * deltaTime;
    }
}