#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>
#include <cstdlib>
#include "GameEntity.h"

class Collider : public GameEntity
{
public:
	Collider(Entity* entity);
	~Collider();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);

	char* type();

	void resolveCollision(GameEntity* collider, GameEntity* object);

	SDL_Point getVelocity();

	bool isDeletable();
};

#endif