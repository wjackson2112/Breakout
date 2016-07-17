#ifndef SLIDER_H
#define SLIDER_H

#include "MenuEntity.h"

class Slider : public MenuEntity
{
private:
	Rect slideRect;
	SDL_Texture* slideTexture;
	double slideValue;
	bool dragging;
public:
	Slider(AssetFactory* assetFactory);

	void handleMousePress(int mouseState, int x, int y);
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY);
	void handleMouseRelease(int mouseState, int x, int y);

	void update(int frameTime);
	void render(SDL_Renderer*);

	void setRect(Rect rect);

	char* type();

};

#endif