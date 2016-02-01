#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>
#include <cstdlib>
#include "PhysicsEntity.h"

class Collider : public PhysicsEntity
{
public:
	Collider(Entity* entity);
	~Collider();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);

	char* type();

	void resolveCollision(PhysicsEntity* collider, PhysicsEntity* object);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getSize();
	SDL_Point getVelocity();

	bool isDeletable();
};

#endif