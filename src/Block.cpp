#include "Block.h"

Block::Block(int x, int y, int width, int height, int* blockCount, TextureFactory* textureFactory, BlockColor color)
{
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;

	r = rand()%0xFF;
	g = rand()%0xFF;
	b = rand()%0xFF;

	visible = true;

	this->textureFactory = textureFactory;

	switch(color){
		case RED:
			this->texture = this->textureFactory->getTexture("./png/RedBlock.png");
			break;
		case ORANGE:
			this->texture = this->textureFactory->getTexture("./png/OrangeBlock.png");
			break;
		case YELLOW:
			this->texture = this->textureFactory->getTexture("./png/YellowBlock.png");
			break;
		case GREEN:
			this->texture = this->textureFactory->getTexture("./png/GreenBlock.png");
			break;
		case BLUE:
			this->texture = this->textureFactory->getTexture("./png/BlueBlock.png");
			break;
		case PURPLE:
			this->texture = this->textureFactory->getTexture("./png/PurpleBlock.png");
			break;
		default:
			break;
	}

	EventManager::Instance()->registerHandler(this);
}

Block::~Block()
{
	EventManager::Instance()->reportGameEvent(BLOCK_DISAPPEARED);
	EventManager::Instance()->deregisterHandler(this);
}

void Block::handleMouseEvents(int mouseState, int x, int y)
{

}

void Block::handleKeyboardEvents(const Uint8* keyStates)
{

}

void Block::handleGameEvents(const Uint8* events)
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

	SDL_Rect drawRect = {posX, posY, width, height};
	SDL_RenderCopy( gRenderer, this->texture, NULL, &drawRect );
}

char* Block::type()
{
	return "Block";
}

void Block::resolveCollision(PhysicsEntity* collider, PhysicsEntity* object)
{
	//Dismiss self if collided with ball
	if(dynamic_cast<Ball*> (object) != NULL)
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