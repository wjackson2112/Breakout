#include "Collider.h"

Collider::Collider(Entity* entity)
{
	this->posX = entity->getOrigin().x;
	this->posY = entity->getOrigin().y;
	this->width = entity->getSize().x;
	this->height = entity->getSize().y;
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

void Collider::resolveCollision(PhysicsEntity* collider, PhysicsEntity* object)
{

}

SDL_Point Collider::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point Collider::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point Collider::getSize()
{
	SDL_Point velocity = {width, height};
	return velocity;
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
