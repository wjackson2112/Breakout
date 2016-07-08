#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "MenuEntity.h"
#include "EventManager.h"
#include "AssetFactory.h"

class Label : public MenuEntity
{
public:
	Label(string texture_file, AssetFactory* assetFactory);
	~Label();

	void setRect(SDL_Rect rect);

	void handleMousePress(int mouseState, int x, int y);
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY);
	void handleMouseRelease(int mouseState, int x, int y);
	
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);

	char* type();

	void update(int frameTime);
	void render(SDL_Renderer* gRenderer);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getSize();
	SDL_Rect  getRect();

};

#endif