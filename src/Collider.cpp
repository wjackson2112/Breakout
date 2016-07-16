#include "Collider.h"

Collider::Collider(Entity* entity)
	: GameEntity("", NULL)
{
	this->rect.x = entity->getRect().x;
	this->rect.y = entity->getRect().y;
	this->rect.w = entity->getRect().w;
	this->rect.h = entity->getRect().h;
}

Collider::~Collider()
{

}

void Collider::handleMouseEvents(int mouseState, int x, int y)
{
	
}

void Collider::handleKeyboardEvents(const Uint8*)
{

}

void Collider::handleGameEvents(const Uint8* events)
{

}

void Collider::update(int frameTime)
{

}

void Collider::render(SDL_Renderer*)
{

}

char* Collider::type()
{
	return "Collider";
}

void Collider::resolveCollision(GameEntity* collider, GameEntity* object)
{

}

SDL_Point Collider::getVelocity()
{
	SDL_Point size = {velX, velY};
	return size;
}

bool Collider::isDeletable()
{
	return false;
}
