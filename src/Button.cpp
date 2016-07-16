#include "Button.h"

Button::Button(string texture_file, AssetFactory* assetFactory, GameEvent event)
	: MenuEntity::MenuEntity(texture_file, assetFactory)
{
	this->event = event;
}

void Button::handleMouseRelease(int mouseButton, int x, int y)
{
	if(mouseButton & SDL_BUTTON(SDL_BUTTON_LEFT) &&
	   x > this->rect.x && 
	   x < this->rect.x + this->rect.w && 
	   y > this->rect.y && 
	   y < this->rect.y + this->rect.h)
	{
		EventManager::Instance()->reportGameEvent(event);
	}
}

char* Button::type()
{
	return "Button";
}

void Button::render(SDL_Renderer* gRenderer)
{
	SDL_Rect renderRect = {this->rect.x, this->rect.y, this->rect.w, this->rect.h};
	SDL_RenderCopy( gRenderer, this->texture, NULL, &renderRect );
}