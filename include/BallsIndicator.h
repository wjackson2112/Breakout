#ifndef BALLS_INDICATOR_H
#define BALLS_INDICATOR_H

#include "UIEntity.h"
#include "AssetFactory.h"

class BallsIndicator : public UIEntity, public IGameEventHandler
{
private:
	int ballsRemaining;
	int gapWidth = Globals::ballWidth / 2;
	AssetFactory* assetFactory;
public:
	BallsIndicator(float x, float y, AssetFactory* assetFactory);
	~BallsIndicator();

	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);
	char* type();

	SDL_Point getCenter();

	bool isDeletable();
};

#endif