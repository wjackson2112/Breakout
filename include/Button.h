#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "UIEntity.h"
#include "EventManager.h"

class Button : public UIEntity
{
private:
	int r, g, b;
	TTF_Font* font;
public:
	Button(const char* fontName);
	~Button();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	char* type();

	void update(int frameTime);
	void render(SDL_Renderer* gRenderer);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getSize();

};

#endif