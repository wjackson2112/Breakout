#include "Block.h"

Block::Block(int x, int y, int* blockCount, IBlockDelegate* delegate)
{
	posX = x;
	posY = y;

	r = rand()%0xFF;
	g = rand()%0xFF;
	b = rand()%0xFF;

	if(delegate)
	{
		this->delegate = delegate;
	}

	visible = true;

	EventManager::Instance()->registerHandler(this);
}

Block::~Block()
{
	if(delegate){
		delegate->blockDisappearing();
	}

	EventManager::Instance()->deregisterHandler(this);
}

Block* Block::clone() const
{
	return new Block(*this);
}

Block* Block::collisionClone() const
{
	Block* newBlock = new Block(*this);
	newBlock->setDelegate(NULL);
	return newBlock;
}

void Block::setDelegate(IBlockDelegate* delegate)
{
	this->delegate = delegate;
}

void Block::handleKeyboardEvents(const Uint8* keyStates)
{

}

void Block::handleGameEvents(int event)
{
	
}

void Block::update(int frameTime)
{

}

void Block::render(SDL_Renderer* gRenderer)
{
	if(!visible)
	{
		return;
	}

	SDL_Rect fillRect = {posX, posY, width, height};
	SDL_SetRenderDrawColor(gRenderer, r, g, b, 0x00);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

void Block::resolveCollision(PhysicsEntity* collidedObject)
{
	//Dismiss self if collided with ball
	if(dynamic_cast<Ball*> (collidedObject) != NULL)
	{
		visible = false;
	}
}

SDL_Point Block::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point Block::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point Block::getSize()
{
	SDL_Point velocity = {width, height};
	return velocity;
}

SDL_Point Block::getVelocity()
{
	SDL_Point size = {velX, velY};
	return size;
}

bool Block::isDeletable()
{
	if(!visible){
		return true;
	}
	return false;
}