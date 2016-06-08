#include "Button.h"

Button::Button(string texture_file, AssetFactory* assetFactory, GameEvent event)
{
	this->event = event;

	this->texture = assetFactory->getAsset<SDL_Texture>(texture_file);
	SDL_QueryTexture(this->texture, NULL, NULL, &(this->rect.w), &(this->rect.h));

	EventManager::Instance()->registerHandler(this);
}

Button::~Button()
{
	EventManager::Instance()->deregisterHandler(this);
}

void Button::setRect(SDL_Rect rect)
{
	this->rect.x = rect.x;
	this->rect.y = rect.y;
	this->rect.w = rect.w;
	this->rect.h = rect.h;
}

GameEvent Button::handleClick(int x, int y)
{
	if(x > this->rect.x && 
	   x < this->rect.x + this->rect.w && 
	   y > this->rect.y && 
	   y < this->rect.y + this->rect.h)
	{
		return this->event;
	}

	return NO_EVENT;
}

void Button::handleMouseEvents(int mouseState, int x, int y)
{

	// if((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && 
	// 	x > this->rect.x && 
	// 	x < this->rect.x + this->rect.w && 
	// 	y > this->rect.y && 
	// 	y < this->rect.y + this->rect.h &&
	// 	lastState == false)
	// {
	// 	lastState = true;
	// }
	// else if(!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && 
	// 		lastState == true)
	// {
	// 	EventManager::Instance()->reportGameEvent(this->event);
	// 	lastState = false;
	// }
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
	SDL_RenderCopy( gRenderer, this->texture, NULL, &this->rect);
}

SDL_Point Button::getCenter()
{
	SDL_Point center = {this->rect.x + this->rect.w/2, this->rect.y + this->rect.h/2};
	return center;
}

SDL_Point Button::getOrigin()
{
	SDL_Point origin = {this->rect.x, this->rect.y};
	return origin;
}

SDL_Point Button::getSize()
{
	SDL_Point velocity = {this->rect.w, this->rect.h};
	return velocity;
}

SDL_Rect  Button::getRect()
{
	return this->rect;
}
