#include "Button.h"

Button::Button(const char* fontName)
{
	this->posX = 100;
	this->posY = 100;
	this->width = 200;
	this->height = 50;
	this->r = 0x22;
	this->g = 0x22;
	this->b = 0x22;

	this->font = TTF_OpenFont("/usr/local/share/fonts/Anonymous Pro.ttf", 90);

	if(font == nullptr)
	{
		std::cout << "Couldn't load font: " << SDL_GetError() << std::endl;
	}

	EventManager::Instance()->registerHandler(this);
}

Button::~Button()
{
	EventManager::Instance()->deregisterHandler(this);
}

void Button::handleMouseEvents(int mouseState, int x, int y)
{
	static bool lastState = false;

	if((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && 
		x > posX && 
		x < posX + width && 
		y > posY && 
		y < posY + height &&
		lastState == false)
	{
		lastState = true;
	}
	else if(!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && 
			lastState == true)
	{
		EventManager::Instance()->reportGameEvent(NEW_GAME);
		lastState = false;
	}
}

void Button::handleKeyboardEvents(const Uint8*)
{

}

void Button::handleGameEvents(const Uint8* events)
{

}

char* Button::type()
{

}

void Button::update(int frameTime)
{

}

void Button::render(SDL_Renderer* gRenderer)
{
	SDL_Rect fillRect = {posX, posY, width, height};
	SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);

	SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, "New Game", textColor);
	SDL_Texture* text = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	SDL_RenderCopy(gRenderer, text, nullptr, &fillRect);

	SDL_FreeSurface(text_surface);
}

SDL_Point Button::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point Button::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point Button::getSize()
{
	SDL_Point velocity = {width, height};
	return velocity;
}