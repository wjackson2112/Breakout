#ifndef SLIDER_H
#define SLIDER_H

#include "MenuEntity.h"

class Slider : public MenuEntity
{
private:
	Rect slideRect;
	SDL_Texture* slideTexture;
	double slideValue;
	string optionPath;
	int controlledValue;
	int controlledMin, controlledMax;
	bool dragging;
public:
	Slider(AssetFactory* assetFactory, Options* options, string optionPath, int min, int max, int paginations);

	void handleMousePress(int mouseState, int x, int y);
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY);
	void handleMouseRelease(int mouseState, int x, int y);

	void update(int frameTime);
	void render(SDL_Renderer*);

	void setRect(Rect rect);

	char* type();

};

#endif