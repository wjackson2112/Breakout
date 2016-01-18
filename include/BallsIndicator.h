#ifndef BALLS_INDICATOR_H
#define BALLS_INDICATOR_H

#include "UIEntity.h"
#include "IBallsIndicatorDelegate.h"

class BallsIndicator : public UIEntity
{
private:
	int ballsRemaining;
	int gapWidth = 10;
	IBallsIndicatorDelegate* delegate;
public:
	BallsIndicator(float x, float y, int ballsRemaining, IBallsIndicatorDelegate* delegate);
	~BallsIndicator();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(int event);
	void update(int frameTime);
	void render(SDL_Renderer*);

	BallsIndicator* clone() const;
	BallsIndicator* collisionClone() const;

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif