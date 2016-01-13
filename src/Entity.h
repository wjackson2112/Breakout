#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "EventManager.h"
#include "IEventHandler.h"
#include "Globals.h"

class Entity : public IEventHandler
{
protected:
	float posX, posY;
	float velX, velY;P
public:
	int width, height;

	float max_vel = 200;

	Entity();
	virtual ~Entity() = 0;

	virtual void handleEvents(const Uint8*) = 0;
	virtual void update(int frameTime) = 0;
	virtual void render(SDL_Renderer*) = 0;
	virtual void resolveCollision(Entity*) = 0;

	virtual Entity* clone() const = 0;
	virtual Entity* collisionClone() const = 0;

	virtual SDL_Point getCenter() = 0;
	virtual SDL_Point getOrigin() = 0;
	virtual SDL_Point getSize() = 0;
	virtual SDL_Point getVelocity() = 0;

	virtual bool isDeletable() = 0;
};

#endif