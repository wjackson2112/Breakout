#include "BallsIndicator.h"

BallsIndicator::BallsIndicator(float x, float y, AssetFactory* assetFactory)
	: UIEntity::UIEntity("./png/Ball.png", assetFactory)
{
	this->ballsRemaining = 0;
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = Globals::ballWidth;
	this->rect.h = Globals::ballHeight;

	EventManager::Instance()->registerGameEventHandler(this);
}

BallsIndicator::~BallsIndicator()
{
	EventManager::Instance()->deregisterGameEventHandler(this);
}

void BallsIndicator::handleGameEvents(const Uint8* events)
{
	if(events[BALL_LOST])
	{
		this->ballsRemaining--;
	}

	if(events[BALL_ADDED])
	{
		this->ballsRemaining += events[BALL_ADDED];
	}
}

void BallsIndicator::update(int frameTime)
{
	if(ballsRemaining < 0){
		EventManager::Instance()->reportGameEvent(BALLS_DEPLETED);
	}
}

void BallsIndicator::render(SDL_Renderer* gRenderer)
{
	for(int i = 0; i < ballsRemaining; i++)
	{
		SDL_Rect renderRect = {(int) this->rect.x + i*gapWidth + i*this->rect.w, (int) this->rect.y, (int) this->rect.w, (int) this->rect.h};
		SDL_RenderCopy( gRenderer, this->texture, NULL, &renderRect );
	}
}

char* BallsIndicator::type()
{
	return "BallsIndicator";
}

bool BallsIndicator::isDeletable()
{
	return false;
}