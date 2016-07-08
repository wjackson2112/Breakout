#ifndef IMOUSE_EVENT_HANDLER_H
#define IMOUSE_EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "EventManager.h"

class IMouseEventHandler
{
public:
	virtual void handleMousePress(int mouseButton, int x, int y) = 0;
	virtual void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY) = 0;
	virtual void handleMouseRelease(int mouseButton, int x, int y) = 0;
};

#endif