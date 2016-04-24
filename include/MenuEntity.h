#ifndef MENU_ENTITY_H
#define MENU_ENTITY_H

#include <SDL2/SDL.h>
#include "Entity.h"

class MenuEntity : public Entity
{
public:
	SDL_Rect rect;
	SDL_Texture* texture;

	virtual void setRect(SDL_Rect rect) = 0;
	virtual SDL_Rect  getRect() = 0;

	virtual void disable() = 0;
	virtual void enable() = 0;

};

#endif