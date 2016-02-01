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
public:
	int width, height;

	//Entity();
	virtual ~Entity() = 0;

	virtual void handleKeyboardEvents(const Uint8*) = 0;
	virtual void handleGameEvents(const Uint8* events) = 0;
	virtual void update(int frameTime) = 0;
	virtual void render(SDL_Renderer*) = 0;

	virtual SDL_Point getCenter() = 0;
	virtual SDL_Point getOrigin() = 0;
	virtual SDL_Point getSize() = 0;

	virtual bool isDeletable() = 0;
};

#endif