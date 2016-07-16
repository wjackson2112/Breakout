#include "Ball.h"

Ball::Ball(Paddle* paddle, AssetFactory* assetFactory)
	: GameEntity("./png/Ball.png", assetFactory)
{
	this->rect.x = -100;
	this->rect.y = -100;
	this->rect.w = Globals::ballWidth;
	this->rect.h = Globals::ballHeight;
	this->max_vel = this->rect.w * 15;
	this->velX = 0.0;
	this->velY = 0.0;

	this->paddleSound = assetFactory->getAsset<Sound>("./sounds/LowBlip.wav");
	this->blockSound = assetFactory->getAsset<Sound>("./sounds/MidBlip.wav");

	this->paddle = paddle;
	this->state = new StateMachine<BallState>(
						//(StateMachine<BallState>::StateMachineCB) &Ball::stateChanged,
						[this](BallState prevState, BallState currState){ return this->stateChanged(prevState, currState); },
						LOST_ST);

	EventManager::Instance()->registerKeyboardEventHandler(this);
}

Ball::~Ball()
{
	EventManager::Instance()->deregisterKeyboardEventHandler(this);
}

void Ball::handleKeyboardEvents(const Uint8* keyStates)
{
	if(keyStates[SDL_SCANCODE_SPACE])
	{
		if(this->state->getState() == WAITING_ST){
			this->state->updateState(FLYING_ST);
			updateVelocityWithAngle(90-((this->paddle->getVelocity().x/this->paddle->max_vel)*45));
		}
	}
}

void Ball::update(int frameTime)
{
	switch(this->state->getState())
	{
		case LOST_ST:
			EventManager::Instance()->reportGameEvent(BALL_LOST);
			this->state->updateState(WAITING_ST);
		case WAITING_ST:
			this->rect.x = this->paddle->getCenter().x - this->rect.w/2.0;
			this->rect.y = this->paddle->getRect().y - this->rect.h - 1;
			break;

		case FLYING_ST:
			this->rect.x += this->velX * (float) frameTime/SDL_GetPerformanceFrequency();

			if((int) this->rect.x < 0)
			{
				this->rect.x = 0;
				this->velX = -(this->velX);
			} 
			else if(this->rect.x > Globals::fieldWidth - this->rect.w)
			{
				this->rect.x = Globals::fieldWidth - this->rect.w;
				this->velX = -(this->velX);
			}

			this->rect.y += this->velY * (float) frameTime/SDL_GetPerformanceFrequency();

			if((int) this->rect.y < 0)
			{
				this->rect.y = 0;
				this->velY = -(this->velY);
			}
			else if(this->rect.y > Globals::fieldHeight)
			{
				this->state->updateState(LOST_ST);
			}

			break;
	}
}

char* Ball::type()
{
	return "Ball";
}

void Ball::resolveCollision(GameEntity* collider, GameEntity* object)
{
	//Bounce off the paddle
	if(dynamic_cast<Paddle*> (object) != NULL)
	{
		int deltaX, deltaY;
		int direction;

		//if(velX >= 0){
		if(this->rect.x + this->rect.w - collider->getRect().x < collider->getRect().x + collider->getRect().w - this->rect.x)
		{
			deltaX = this->rect.x + this->rect.w - collider->getRect().x;
			if(this->velX != 0)
				deltaY = (this->velY/this->velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 0;
		}
		else
		{
			deltaX = collider->getRect().x + collider->getRect().w - this->rect.x;
			if(this->velX != 0)
				deltaY = (this->velY/this->velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 1;
		}

		if(this->velY >= 0){
			if(this->rect.y + this->rect.h - collider->getRect().y < abs(deltaY)){
				deltaY = this->rect.y + this->rect.h - collider->getRect().y;
				deltaX = (this->velX/this->velY)*deltaY;
				direction = 2;
			}
		}
		else
		{
			if(collider->getRect().y + collider->getRect().h - this->rect.y < abs(deltaY))
			{
				deltaY = collider->getRect().y + collider->getRect().h - this->rect.y;
				deltaX = this->velX/this->velY*deltaY;
				direction = 3;
			}	
		}

		if(this->velX >= 0)
			this->rect.x -= deltaX;
		else
			this->rect.x += deltaX;

		if(this->velY >= 0)
			this->rect.y -= deltaY;
		else
			this->rect.y += deltaY;

		switch(direction)
		{
			//left
			case 0:
				if(this->velX > 0)
				{
					this->velX = -(this->velX);
				}
				break;
			//right 
			case 1:
				if(this->velX < 0)
				{
					this->velX = -(this->velX);					
				}
				break;
			//top
			case 2:
			{
				float angle = (((float) collider->getCenter().x - (float) getCenter().x)/((float) collider->getRect().w/2) * 45) + 90;
				updateVelocityWithAngle(angle);
				break;
			}
			//bottom 
			case 3:
				if(this->velY < 0)
				{
					this->velY = -(this->velY);
				}
				break;
			default:
				break;
		}

		paddleSound->play();
	}
		//Bounce off the paddle
	else if(dynamic_cast<Block*> (object) != NULL)
	{
		int deltaX, deltaY;
		int direction;

		//if(velX >= 0){
		if(this->rect.x + this->rect.w - collider->getRect().x < collider->getRect().x + collider->getRect().w - this->rect.x)
		{
			deltaX = this->rect.x + this->rect.w - collider->getRect().x;
			if(this->velX != 0)
				deltaY = (this->velY/this->velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 0;
		}
		else
		{
			deltaX = collider->getRect().x + collider->getRect().w - this->rect.x;
			if(this->velX != 0)
				deltaY = (this->velY/this->velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 1;
		}

		if(this->rect.y + this->rect.h - collider->getRect().y < collider->getRect().y + collider->getRect().h - this->rect.y){
			if(this->rect.y + this->rect.h - collider->getRect().y < abs(deltaY)){
				deltaY = this->rect.y + this->rect.h - collider->getRect().y;
				deltaX = (this->velX/this->velY)*deltaY;
				direction = 2;
			}
		}
		else
		{
			if(collider->getRect().y + collider->getRect().h - this->rect.y < abs(deltaY))
			{
				deltaY = collider->getRect().y + collider->getRect().h - this->rect.y;
				deltaX = this->velX/this->velY*deltaY;
				direction = 3;
			}	
		}

		if(this->velX >= 0)
			this->rect.x -= deltaX;
		else
			this->rect.x += deltaX;

		if(this->velY >= 0)
			this->rect.y -= deltaY;
		else
			this->rect.y += deltaY;

		switch(direction)
		{
			//left
			case 0:
				if(this->velX > 0)
				{
					this->velX = -(this->velX);
				}
				break;
			//right 
			case 1:
				if(this->velX < 0)
				{
					this->velX = -(this->velX);					
				}
				break;
			//top
			case 2:
			{
				if(this->velY > 0)
				{
					this->velY = -(this->velY);
				}
				break;
			}
			//bottom 
			case 3:
				if(this->velY < 0)
				{
					this->velY = -(this->velY);
				}
				break;
			default:
				break;
		}

		blockSound->play();
	}
}

void Ball::updateVelocityWithAngle(float degrees)
{
	float radians = degrees * 3.14159/180;
	this->velX = this->max_vel * cos(radians);
	this->velY = -(this->max_vel * sin(radians));
}

void Ball::stateChanged(BallState prevState, BallState currState)
{
	switch(currState)
	{
		case LOST_ST:
			break;
		case WAITING_ST:
			break;
		case FLYING_ST:
			break;
	}
}