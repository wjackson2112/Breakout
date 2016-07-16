#include "Block.h"

Block::Block(int x, int y, int width, int height, int* blockCount, AssetFactory* assetFactory, BlockColor color)
	: GameEntity("", NULL)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = width;
	this->rect.h = height;

	this->assetFactory = assetFactory;

	this->state = new StateMachine<BlockState>(
						[this](BlockState prevState, BlockState currState) { return this->stateChanged(prevState, currState); },
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

	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(this->texture, 255);

	this->effects = new Effects(this->texture,
								[this](void){ return this->alphaTransitionComplete(); }, 
								//(Effects::EffectsCB) &Block::alphaTransitionComplete, 
								NULL);
}

Block::~Block()
{
	EventManager::Instance()->reportGameEvent(BLOCK_DISAPPEARED);
}

void Block::render(SDL_Renderer* gRenderer)
{
	switch(this->state->getState()){
		case IDLE_ST:
		case FADING_ST:
		{
			this->effects->apply();
			SDL_Rect renderRect = {this->rect.x, this->rect.y, this->rect.w, this->rect.h};
			SDL_RenderCopy( gRenderer, this->texture, NULL, &renderRect );
			break;
		}
	}
}

char* Block::type()
{
	return "Block";
}

void Block::resolveCollision(GameEntity* collider, GameEntity* object)
{
	//Dismiss self if collided with ball
	if(dynamic_cast<Ball*> (object) != NULL)
	{
		this->state->updateState(FADING_ST);
	}
}

bool Block::isDeletable()
{
	if(this->state->getState() == GONE_ST){
		return true;
	}
	return false;
}

void Block::alphaTransitionComplete()
{
	this->state->updateState(GONE_ST);
}

void Block::stateChanged(BlockState prevState, BlockState currState){
	switch(currState)
	{
		case IDLE_ST:
			break;
		case FADING_ST:
			switch(prevState)
			{
				case IDLE_ST:
					this->effects->addAlphaTransition(250, 255, 0);
					break;
			}
			break;
		case GONE_ST:
			break;
	}
}