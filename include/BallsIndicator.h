#ifndef BALLS_INDICATOR_H
#define BALLS_INDICATOR_H

#include "UIEntity.h"
#include "TextureFactory.h"

class BallsIndicator : public UIEntity
{
private:
	int ballsRemaining;
	int gapWidth = Globals::ballWidth / 2;
	TextureFactory* textureFactory;
	SDL_Texture* texture;
public:
	BallsIndicator(float x, float y, TextureFactory* textureFactory);
	~BallsIndicator();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);
	char* type();

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif