#ifndef LABEL_H
#define LABEL_H

#include "MenuEntity.h"
#include "AssetFactory.h"
#include "Options.h"

class Label : public MenuEntity
{
public:
	Label(string texture_file, AssetFactory* assetFactory, Options* options);

	void handleMousePress(int mouseState, int x, int y){};
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY){};
	void handleMouseRelease(int mouseState, int x, int y){};

	char* type();

};

#endif