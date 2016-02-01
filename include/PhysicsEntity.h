#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include <SDL2/SDL.h>
#include "Entity.h"

class PhysicsEntity : public Entity
{
protected:
	float velX, velY;
public:
	float max_vel = 200;
	virtual void resolveCollision(PhysicsEntity* collider, PhysicsEntity* object) = 0;
	virtual SDL_Point getVelocity() = 0;
};

#endif