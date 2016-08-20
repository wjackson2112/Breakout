#ifndef MENU_ENTITY_H
#define MENU_ENTITY_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "EventManager.h"
#include "IMouseEventHandler.h"
#include "IGameEventHandler.h"
#include "IKeyboardEventHandler.h"
#include "Options.h"

class MenuEntity : public Entity, public IMouseEventHandler
{
protected:
	Options* options;

public:
	MenuEntity(string texture_file, AssetFactory* assetFactory, Options* options);
	virtual ~MenuEntity(){};

	virtual void handleMousePress(int mouseState, int x, int y){};
	virtual void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY){};
	virtual void handleMouseRelease(int mouseState, int x, int y){};

	virtual void update(int frameTime){};

	virtual void setRect(Rect rect);
};

#endif