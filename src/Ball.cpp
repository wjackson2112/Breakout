#include "Ball.h"

Ball::Ball(Paddle* paddle, AssetFactory* assetFactory)
{
	EventManager::Instance()->registerHandler(this);
	posX = -100;
	posY = -100;
	velX = 0;
	velY = 0;

	this->assetFactory = assetFactory;
	this->texture = assetFactory->getAsset<SDL_Texture>("./png/Ball.png");

	this->paddle = paddle;
	this->state = new StateMachine<BallState>(
						(StateMachine<BallState>::StateMachineCB) &Ball::stateChanged,
						LOST_ST);
}

Ball::~Ball()
{
	EventManager::Instance()->deregisterHandler(this);
}

void Ball::updateVelocityWithAngle(float degrees)
{
	float radians = degrees * 3.14159/180;
	velX = max_vel * cos(radians);
	velY = -(max_vel * sin(radians));
}

void Ball::render(SDL_Renderer* gRenderer)
{
	SDL_Rect drawRect = {posX, posY, width, height};
	SDL_RenderCopy( gRenderer, this->texture, NULL, &drawRect );
}

void Ball::update(int frameTime)
{
	switch(this->state->getState())
	{
		case LOST_ST:
			EventManager::Instance()->reportGameEvent(BALL_LOST);
			this->state->updateState(WAITING_ST);
		case WAITING_ST:
			posX = paddle->getCenter().x - width/2;
			posY = paddle->getOrigin().y - height;
			break;

		case FLYING_ST:
			posX += velX * (float) frameTime/SDL_GetPerformanceFrequency();

			if(posX < Globals::xOffset)
			{
				posX = Globals::xOffset;
				velX = -velX;
			} 
			else if(posX > Globals::xOffset + Globals::fieldWidth - width)
			{
				posX = Globals::xOffset + Globals::fieldWidth - width;
				velX = -velX;
			}

			posY += velY * (float) frameTime/SDL_GetPerformanceFrequency();

			if(posY < Globals::yOffset)
			{
				posY = Globals::yOffset;
				velY = -velY;
			}
			else if(posY > Globals::yOffset + Globals::fieldHeight)
			{
				
				this->state->updateState(LOST_ST);
			}

			break;
	}
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

char* Ball::type()
{
	return "Ball";
}

void Ball::handleMouseEvents(int mouseState, int x, int y)
{

}

void Ball::handleKeyboardEvents(const Uint8* keyStates)
{
	if(keyStates[SDL_SCANCODE_SPACE])
	{
		if(this->state->getState() == WAITING_ST){
			this->state->updateState(FLYING_ST);
			updateVelocityWithAngle(90-((paddle->getVelocity().x/paddle->max_vel)*45));
		}
	}
}

void Ball::handleGameEvents(const Uint8* events)
{

}

void Ball::resolveCollision(PhysicsEntity* collider, PhysicsEntity* object)
{
	//std::cout << "Ball resolving" << std::endl;
	//Bounce off the paddle
	if(dynamic_cast<Paddle*> (object) != NULL)
	{
		int deltaX, deltaY;
		int direction;

		//if(velX >= 0){
		if(posX + width - collider->getOrigin().x < collider->getOrigin().x + collider->getSize().x - posX)
		{
			deltaX = posX + width - collider->getOrigin().x;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 0;
		}
		else
		{
			deltaX = collider->getOrigin().x + collider->getSize().x - posX;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 1;
		}

		if(velY >= 0){
			if(posY + height - collider->getOrigin().y < abs(deltaY)){
				deltaY = posY + height - collider->getOrigin().y;
				deltaX = (velX/velY)*deltaY;
				direction = 2;
			}
		}
		else
		{
			if(collider->getOrigin().y + collider->getSize().y - posY < abs(deltaY))
			{
				deltaY = collider->getOrigin().y + collider->getSize().y - posY;
				deltaX = velX/velY*deltaY;
				direction = 3;
			}	
		}

		if(velX >= 0)
			posX -= deltaX;
		else
			posX += deltaX;

		if(velY >= 0)
			posY -= deltaY;
		else
			posY += deltaY;

		switch(direction)
		{
			//left
			case 0:
				if(velX > 0)
				{
					velX = -velX;
				}
				break;
			//right 
			case 1:
				if(velX < 0)
				{
					velX = -velX;					
				}
				break;
			//top
			case 2:
			{
				float angle = (((float) collider->getCenter().x - (float) getCenter().x)/((float) collider->getSize().x/2) * 45) + 90;
				updateVelocityWithAngle(angle);
				break;
			}
			//bottom 
			case 3:
				if(velY < 0)
				{
					velY = -velY;
				}
				break;
			default:
				break;
		}
	}
		//Bounce off the paddle
	else if(dynamic_cast<Block*> (object) != NULL)
	{
		int deltaX, deltaY;
		int direction;

		//if(velX >= 0){
		if(posX + width - collider->getOrigin().x < collider->getOrigin().x + collider->getSize().x - posX)
		{
			deltaX = posX + width - collider->getOrigin().x;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 0;
		}
		else
		{
			deltaX = collider->getOrigin().x + collider->getSize().x - posX;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 1;
		}

		if(posY + height - collider->getOrigin().y < collider->getOrigin().y + collider->getSize().y - posY){
			if(posY + height - collider->getOrigin().y < abs(deltaY)){
				deltaY = posY + height - collider->getOrigin().y;
				deltaX = (velX/velY)*deltaY;
				direction = 2;
			}
		}
		else
		{
			if(collider->getOrigin().y + collider->getSize().y - posY < abs(deltaY))
			{
				deltaY = collider->getOrigin().y + collider->getSize().y - posY;
				deltaX = velX/velY*deltaY;
				direction = 3;
			}	
		}

		if(velX >= 0)
			posX -= deltaX;
		else
			posX += deltaX;

		if(velY >= 0)
			posY -= deltaY;
		else
			posY += deltaY;

		switch(direction)
		{
			//left
			case 0:
				if(velX > 0)
				{
					velX = -velX;
				}
				break;
			//right 
			case 1:
				if(velX < 0)
				{
					velX = -velX;					
				}
				break;
			//top
			case 2:
			{
				if(velY > 0)
				{
					velY = -velY;
				}
				break;
			}
			//bottom 
			case 3:
				if(velY < 0)
				{
					velY = -velY;
				}
				break;
			default:
				break;
		}
	}
}

SDL_Point Ball::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point Ball::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point Ball::getVelocity()
{
	SDL_Point velocity = {velX, velY};
	return velocity;
}

SDL_Point Ball::getSize()
{
	SDL_Point size = {width, height};
	return size;
}

bool Ball::isDeletable()
{
	return false;
}