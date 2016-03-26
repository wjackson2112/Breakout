#include "Block.h"

Block::Block(int x, int y, int width, int height, int* blockCount, AssetFactory* assetFactory, BlockColor color)

{
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;

	r = rand()%0xFF;
	g = rand()%0xFF;
	b = rand()%0xFF;

	this->assetFactory = assetFactory;

	this->state = new StateMachine<BlockState>(
						(StateMachine<BlockState>::StateMachineCB) &Block::stateChanged, 
						IDLE_ST);

	switch(color){
		case RED:
			this->texture = this->assetFactory->getAsset<SDL_Texture>("./png/RedBlock.png");
			break;
		case ORANGE:
			this->texture = this->assetFactory->getAsset<SDL_Texture>("./png/OrangeBlock.png");
			break;
		case YELLOW:
			this->texture = this->assetFactory->getAsset<SDL_Texture>("./png/YellowBlock.png");
			break;
		case GREEN:
			this->texture = this->assetFactory->getAsset<SDL_Texture>("./png/GreenBlock.png");
			break;
		case BLUE:
			this->texture = this->assetFactory->getAsset<SDL_Texture>("./png/BlueBlock.png");
			break;
		case PURPLE:
			this->texture = this->assetFactory->getAsset<SDL_Texture>("./png/PurpleBlock.png");
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
	switch(this->state->getState()){
		case IDLE_ST:
			SDL_Rect drawRect = {posX, posY, width, height};
			SDL_RenderCopy( gRenderer, this->texture, NULL, &drawRect );	
			break;	
	}

}

void Block::stateChanged(BlockState prevState, BlockState currState){
	switch(currState)
	{
		case IDLE_ST:
			std::cout << "Changed to IDLE" << std::endl;
			break;
		case FADING_ST:
			std::cout << "Changed to FADING" << std::endl;
			break;
		case GONE_ST:
			std::cout << "Changed to GONE" << std::endl;
			break;
	}
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
		this->state->updateState(GONE_ST);
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
	if(this->state->getState() == GONE_ST){
		return true;
	}
	return false;
}