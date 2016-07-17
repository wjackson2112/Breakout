#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <iostream>
#include "EventManager.h"
#include "Globals.h"
#include "AssetFactory.h"
#include "Rect.h"

class Entity
{
protected:
	Rect rect;
	SDL_Texture* texture;
public:

	Entity(string texture_file, AssetFactory* assetFactory);
	
	virtual char* type();

	virtual void render(SDL_Renderer*);
	virtual void update(int frameTime){};

	SDL_Point getCenter();

	virtual void setRect(Rect rect);
	Rect getRect();
};

#endif