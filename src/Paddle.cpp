#include "Paddle.h"
#include "Ball.h"

Paddle::Paddle(float x, float y, AssetFactory* assetFactory)
	: GameEntity("./png/Paddle.png", assetFactory)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = Globals::paddleWidth;
	this->rect.h = Globals::paddleHeight;
	this->max_vel = this->rect.w * 2.5;
	this->accel = max_vel * 5;

	EventManager::Instance()->registerKeyboardEventHandler(this);
}

Paddle::~Paddle()
{
	EventManager::Instance()->deregisterKeyboardEventHandler(this);
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

void Paddle::update(int frameTime)
{
	if(this->rect.x + velX * (float) frameTime/SDL_GetPerformanceFrequency() >= 0 && 
	   this->rect.x + velX * (float) frameTime/SDL_GetPerformanceFrequency() + this->rect.w <= Globals::fieldWidth)
	{
		velX += accelX * (float) frameTime/SDL_GetPerformanceFrequency();
		if(abs(velX) > max_vel)
		{
			if(velX < 0)
				velX = -max_vel;
			else
				velX = max_vel;
		}
		this->rect.x += velX * (float) frameTime/SDL_GetPerformanceFrequency();
	} 
	else if(this->rect.x + velX * (float) frameTime/SDL_GetPerformanceFrequency() < 0)
	{
		this->rect.x = 0;
	}
	else if(this->rect.x + velX * (float) frameTime/SDL_GetPerformanceFrequency() + this->rect.w > Globals::fieldWidth)
	{
		this->rect.x = Globals::fieldWidth - this->rect.w;
	}
}

char* Paddle::type()
{
	return "Paddle";
}

