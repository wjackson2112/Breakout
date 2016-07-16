#ifndef IKEYBOARD_EVENT_HANDLER_H
#define IKEYBOARD_EVENT_HANDLER_H

#include <SDL2/SDL.h>

class IKeyboardEventHandler
{
public:
	virtual void handleKeyboardEvents(const Uint8*) = 0;
};

#endif