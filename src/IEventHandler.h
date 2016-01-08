#ifndef IEVENT_HANDLER_H
#define IEVENT_HANDLER_H

#include <SDL2/SDL.h>

class IEventHandler
{
public:
	virtual void handleEvents(const Uint8*) = 0;
};

#endif