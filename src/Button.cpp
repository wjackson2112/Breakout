#include "Button.h"

Button::Button(const char* fontName, const char* text, GameEvent event, int x, int y)
{
	this->posX = x;
	this->posY = y;
	this->width = Globals::screenWidth / 4;
	this->height = this->width / 4;
	this->r = 0x22;
	this->g = 0x22;
	this->b = 0x22;
	this->text = text;
	this->event = event;

	this->font = TTF_OpenFont(fontName, 180);

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
		EventManager::Instance()->reportGameEvent(this->event);
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
	return "Button";
}

void Button::update(int frameTime)
{

}

void Button::render(SDL_Renderer* gRenderer)
{
	SDL_Rect fillRect = {posX, posY, width, height};
	//SDL_SetRenderDrawColor(gRenderer, r, g, b, 0xFF);
	//SDL_RenderFillRect(gRenderer, &fillRect);

	SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, this->text, textColor);
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