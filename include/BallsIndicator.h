#ifndef BALLS_INDICATOR_H
#define BALLS_INDICATOR_H

#include "UIEntity.h"

class BallsIndicator : public UIEntity
{
private:
	int ballsRemaining;
	int gapWidth = 10;
public:
	BallsIndicator(float x, float y, int ballsRemaining);
	~BallsIndicator();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif