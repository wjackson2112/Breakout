#include "Label.h"

Label::Label(string texture_file, AssetFactory* assetFactory)
{
	this->texture = assetFactory->getAsset<SDL_Texture>(texture_file);
	SDL_QueryTexture(this->texture, NULL, NULL, &(this->rect.w), &(this->rect.h));
}

Label::~Label()
{

}

void Label::setRect(SDL_Rect rect)
{
	this->rect.x = rect.x;
	this->rect.y = rect.y;
	this->rect.w = rect.w;
	this->rect.h = rect.h;
}

GameEvent Label::handleClick(int x, int y)
{
	return NO_EVENT;
}

void Label::handleMouseEvents(int mouseState, int x, int y)
{

}

void Label::handleKeyboardEvents(const Uint8*)
{

}

void Label::handleGameEvents(const Uint8* events)
{

}

char* Label::type()
{
	return "Label";
}

void Label::update(int frameTime)
{

}

void Label::render(SDL_Renderer* gRenderer)
{
	SDL_RenderCopy( gRenderer, this->texture, NULL, &this->rect);
}

SDL_Point Label::getCenter()
{
	SDL_Point center = {this->rect.x + this->rect.w/2, this->rect.y + this->rect.h/2};
	return center;
}

SDL_Point Label::getOrigin()
{
	SDL_Point origin = {this->rect.x, this->rect.y};
	return origin;
}

SDL_Point Label::getSize()
{
	SDL_Point velocity = {this->rect.w, this->rect.h};
	return velocity;
}

SDL_Rect  Label::getRect()
{
	return this->rect;
}
