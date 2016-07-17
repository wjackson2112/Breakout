#include "Entity.h"

Entity::Entity(string texture_file, AssetFactory* assetFactory)
{
	int width, height;

	this->rect = Rect(0.0, 0.0, 0.0, 0.0);

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

void Entity::setRect(Rect rect)
{
	this->rect = rect;
}

Rect Entity::getRect()
{
	return this->rect;
}