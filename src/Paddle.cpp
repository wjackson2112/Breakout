#include "Paddle.h"
#include "Ball.h"

Paddle::Paddle(float x, float y, AssetFactory* assetFactory)
{
	posX = x + Globals::xOffset;
	posY = y + Globals::yOffset;
	velX = 0;
	velY = 0;

	this->assetFactory = assetFactory;
	this->texture = assetFactory->getAsset<SDL_Texture>("./png/Paddle.png");

	EventManager::Instance()->registerHandler(this);
}

Paddle::~Paddle()
{
	EventManager::Instance()->deregisterHandler(this);
}

void Paddle::render(SDL_Renderer* gRenderer)
{
	SDL_Rect drawRect = {posX, posY, width, height};
	SDL_RenderCopy( gRenderer, this->texture, NULL, &drawRect );
}

void Paddle::update(int frameTime)
{
	if(posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() >= Globals::xOffset && 
	   posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() + width <= Globals::xOffset + Globals::fieldWidth)
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
	else if(posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() < Globals::xOffset)
	{
		posX = Globals::xOffset;
	}
	else if(posX + velX * (float) frameTime/SDL_GetPerformanceFrequency() + width > Globals::xOffset + Globals::fieldWidth)
	{
		posX = Globals::xOffset + Globals::fieldWidth - width;
	}
}

void stateChanged(PaddleState prevState, PaddleState currState)
{
	
}

char* Paddle::type()
{
	return "Paddle";
}

void Paddle::handleMouseEvents(int mouseState, int x, int y)
{
	
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

void Paddle::handleGameEvents(const Uint8* events)
{
	
}

void Paddle::resolveCollision(PhysicsEntity* collider, PhysicsEntity* object)
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