#include "Entity.h"

Entity::Entity(string texture_file, AssetFactory* assetFactory)
{
	int width, height;

	this->rect.x = 0.0f;
	this->rect.y = 0.0f;
	this->rect.w = 0.0f;
	this->rect.h = 0.0f;

	if(texture_file != "" && assetFactory != NULL)
	{
		this->texture = assetFactory->getAsset<SDL_Texture>(texture_file);
		SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
		this->rect.w = width;
		this->rect.h = height;
	}
}

char* Entity::type()
{
	return "Entity";
}

void Entity::render(SDL_Renderer* gRenderer)
{
	SDL_Rect renderRect = {this->rect.x, this->rect.y, this->rect.w, this->rect.h};
	SDL_RenderCopy( gRenderer, this->texture, NULL, &renderRect );
}

SDL_Point Entity::getCenter()
{
	SDL_Point center = {this->rect.x + this->rect.w/2, this->rect.y + this->rect.h/2};
	return center;
}

void Entity::setRect(floatRect rect)
{
	this->rect.x = rect.x;
	this->rect.y = rect.y;
	this->rect.w = rect.w;
	this->rect.h = rect.h;
}

floatRect Entity::getRect()
{
	return this->rect;
}