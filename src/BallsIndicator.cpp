#include "BallsIndicator.h"

BallsIndicator::BallsIndicator(float x, float y, int ballsRemaining)
{
	this->ballsRemaining = ballsRemaining;
	posX = x;
	posY = y;
	width = 20;
	height = 20;

	EventManager::Instance()->registerHandler(this);
}

BallsIndicator::~BallsIndicator()
{
	EventManager::Instance()->deregisterHandler(this);
}

void BallsIndicator::handleKeyboardEvents(const Uint8*)
{

}

void BallsIndicator::handleGameEvents(const Uint8* events)
{
	if(events[BALL_LOST])
	{
		std::cout << "ballsRemaining: " << ballsRemaining << std::endl;
		if(ballsRemaining > 0){
			this->ballsRemaining--;			
		} else {
			EventManager::Instance()->reportGameEvent(BALLS_DEPLETED);
		}
	}
}

void BallsIndicator::update(int frameTime)
{

}

void BallsIndicator::render(SDL_Renderer* gRenderer)
{
	for(int i = 0; i < ballsRemaining; i++)
	{
		SDL_Rect fillRect = {posX + i*width + i*gapWidth, posY, width, height};
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0x00);
		SDL_RenderFillRect(gRenderer, &fillRect);
	}
}

SDL_Point BallsIndicator::getCenter()
{
	SDL_Point center = {posX + width/2, posY + height/2};
	return center;
}

SDL_Point BallsIndicator::getOrigin()
{
	SDL_Point origin = {posX, posY};
	return origin;
}

SDL_Point BallsIndicator::getSize()
{
	SDL_Point size = {width, height};
	return size;
}

bool BallsIndicator::isDeletable()
{
	return false;
}