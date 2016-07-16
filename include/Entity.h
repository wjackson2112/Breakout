#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "EventManager.h"
#include "Globals.h"
#include "AssetFactory.h"

typedef struct floatRect_s
{
	float x;
	float y;
	float w;
	float h;
} floatRect;

class Entity
{
protected:
	floatRect rect;
	SDL_Texture* texture;
public:

	Entity(string texture_file, AssetFactory* assetFactory);
	
	virtual char* type();

	virtual void render(SDL_Renderer*);
	virtual void update(int frameTime){};

	SDL_Point getCenter();

	void 	  setRect(floatRect rect);
	floatRect getRect();
};

#endif