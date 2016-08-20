#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "MenuEntity.h"
#include "EventManager.h"
#include "AssetFactory.h"
#include "Options.h"

class Button : public MenuEntity, public IMouseEventHandler
{
private:
	GameEvent event;
	bool lastState = false;
public:
	Button(string texture_file, AssetFactory* assetFactory, Options* options, GameEvent event);

	void handleMousePress(int mouseState, int x, int y){};
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY){};
	void handleMouseRelease(int mouseState, int x, int y);

	char* type();
	
	void render(SDL_Renderer* gRenderer);
};

#endif