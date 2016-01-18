#include "Paddle.h"

Paddle::Paddle(float x, float y)
{
	posX = x;
	posY = y;
	velX = 0;
	velY = 0;

	EventManager::Instance()->registerHandler(this);
}

Paddle::~Paddle()
{
	EventManager::Instance()->deregisterHandler(this);
}

Paddle* Paddle::clone() const
{
	return new Paddle(*this);
}

Paddle* Paddle::collisionClone() const
{
	Paddle* newPaddle = new Paddle(*this);
	return newPaddle;
}

void Paddle::render(SDL_Renderer* gRenderer)
{
	SDL_Rect fillRect = {posX, posY, width, height};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

void Paddle::update(int frameTime)
{
	if(posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() >= 0 && 
	   posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() + width <= SCREEN_WIDTH)
	{
		velX += accelX * (float) frameTime/SDL_GetPerformanceFrequency();
		if(abs(velX) > max_vel)
		{
			if(velX < 0)
				velX = -max_vel;
			else
				velX = max_vel;
		}
		posX += velX * (float) frameTime/SDL_GetPerformanceFrequency();
	} 
	else if(posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() < 0)
	{
		posX = 0;
	}
	else if(posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() + width > SCREEN_WIDTH)
	{
		posX = SCREEN_WIDTH - width;
	}
}

void Paddle::handleKeyboardEvents(const Uint8* keyStates)
{
	static bool lastLeftState = false;
	static bool lastRightState = false;
	if(keyStates[SDL_SCANCODE_LEFT])
	{
		if(!lastLeftState)
			velX = 0;
		accelX = -accel;
	}
	
	if(keyStates[SDL_SCANCODE_RIGHT])
	{
		if(!lastRightState)
			velX = 0;
		accelX = accel;
	}

	if(!keyStates[SDL_SCANCODE_LEFT] && !keyStates[SDL_SCANCODE_RIGHT])
	{
		accelX = 0;
		velX = 0;
	}

	lastLeftState = keyStates[SDL_SCANCODE_LEFT];
	lastRightState = keyStates[SDL_SCANCODE_RIGHT];
}

void Paddle::handleGameEvents(int event)
{
	
}

void Paddle::resolveCollision(PhysicsEntity* collidedObject)
{

}

SDL_Point Paddle::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point Paddle::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point Paddle::getVelocity()
{
	SDL_Point velocity = {velX, velY};
	return velocity;
}

SDL_Point Paddle::getSize()
{
	SDL_Point size = {width, height};
	return size;
}

bool Paddle::isDeletable()
{
	return false;
}