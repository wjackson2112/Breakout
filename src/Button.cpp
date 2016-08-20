#include "Button.h"

Button::Button(string texture_file, AssetFactory* assetFactory, Options* options, GameEvent event)
	: MenuEntity::MenuEntity(texture_file, assetFactory, options)
{
	this->event = event;
}

void Button::handleMouseRelease(int mouseButton, int x, int y)
{
	if(mouseButton & SDL_BUTTON(SDL_BUTTON_LEFT) &&
	   this->rect.contains(x, y))
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