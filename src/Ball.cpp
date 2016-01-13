#include "Ball.h"

Ball::Ball(Paddle* paddle)
{
	EventManager::Instance()->registerHandler(this);
	posX = 32;
	posY = 420;
	velX = 0;
	velY = 0;

	this->paddle = paddle;
	machineState = WAITING_ST;
	//EventManager::Instance()->registerHandler(this);
}

Ball::~Ball()
{
	EventManager::Instance()->deregisterHandler(this);
}

Ball* Ball::clone() const
{
	return new Ball(*this);
}

Ball* Ball::collisionClone() const
{
	Ball* newBall = new Ball(*this);
	newBall->paddle = NULL;
	newBall->machineState = WAITING_ST;
	return newBall;
}

void Ball::updateVelocityWithAngle(float degrees)
{
	float radians = degrees * 3.14159/180;
	velX = max_vel * cos(radians);
	velY = -(max_vel * sin(radians));
}

void Ball::render(SDL_Renderer* gRenderer)
{
	SDL_Rect fillRect = {posX, posY, width, height};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0x00);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

void Ball::update(int frameTime)
{
	switch(machineState)
	{
		case WAITING_ST:
			posX = paddle->getCenter().x - width/2;
			posY = paddle->getOrigin().y - height;
			break;

		case FLYING_ST:
			posX += velX * (float) frameTime/SDL_GetPerformanceFrequency();

			if(posX < 0)
			{
				posX = 0;
				velX = -velX;
			} 
			else if(posX > SCREEN_WIDTH - width)
			{
				posX = SCREEN_WIDTH - width;
				velX = -velX;
			}

			posY += velY * (float) frameTime/SDL_GetPerformanceFrequency();

			if(posY < 0)
			{
				posY = 0;
				velY = -velY;
			}
			else if(posY > SCREEN_HEIGHT)
			{
				machineState = WAITING_ST;
			}

			break;
	}
}

void Ball::handleEvents(const Uint8* keyStates)
{
	if(keyStates[SDL_SCANCODE_SPACE])
	{
		if(machineState == WAITING_ST){
			machineState = FLYING_ST;
			updateVelocityWithAngle(90-((paddle->getVelocity().x/paddle->max_vel)*45));
		}
	}
}

void Ball::resolveCollision(PhysicsEntity* collidedObject)
{
	//std::cout << "Ball resolving" << std::endl;
	//Bounce off the paddle
	if(dynamic_cast<Paddle*> (collidedObject) != NULL)
	{
		int deltaX, deltaY;
		int direction;

		//if(velX >= 0){
		if(posX + width - collidedObject->getOrigin().x < collidedObject->getOrigin().x + collidedObject->getSize().x - posX)
		{
			deltaX = posX + width - collidedObject->getOrigin().x;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 0;
		}
		else
		{
			deltaX = collidedObject->getOrigin().x + collidedObject->getSize().x - posX;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 1;
		}

		if(velY >= 0){
			if(posY + height - collidedObject->getOrigin().y < abs(deltaY)){
				deltaY = posY + height - collidedObject->getOrigin().y;
				deltaX = (velX/velY)*deltaY;
				direction = 2;
			}
		}
		else
		{
			if(collidedObject->getOrigin().y + collidedObject->getSize().y - posY < abs(deltaY))
			{
				deltaY = collidedObject->getOrigin().y + collidedObject->getSize().y - posY;
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
				float angle = (((float) collidedObject->getCenter().x - (float) getCenter().x)/((float) collidedObject->getSize().x/2) * 45) + 90;
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
	else if(dynamic_cast<Block*> (collidedObject) != NULL)
	{
		int deltaX, deltaY;
		int direction;

		//if(velX >= 0){
		if(posX + width - collidedObject->getOrigin().x < collidedObject->getOrigin().x + collidedObject->getSize().x - posX)
		{
			deltaX = posX + width - collidedObject->getOrigin().x;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 0;
		}
		else
		{
			deltaX = collidedObject->getOrigin().x + collidedObject->getSize().x - posX;
			if(velX != 0)
				deltaY = (velY/velX)*deltaX;
			else
				deltaY = INT_MAX;
			direction = 1;
		}

		if(posY + height - collidedObject->getOrigin().y < collidedObject->getOrigin().y + collidedObject->getSize().y - posY){
			if(posY + height - collidedObject->getOrigin().y < abs(deltaY)){
				deltaY = posY + height - collidedObject->getOrigin().y;
				deltaX = (velX/velY)*deltaY;
				direction = 2;
			}
		}
		else
		{
			if(collidedObject->getOrigin().y + collidedObject->getSize().y - posY < abs(deltaY))
			{
				deltaY = collidedObject->getOrigin().y + collidedObject->getSize().y - posY;
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