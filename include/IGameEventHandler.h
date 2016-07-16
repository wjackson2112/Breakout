#ifndef IGAME_EVENT_HANDLER_H
#define IGAME_EVENT_HANDLER_H

#include <SDL2/SDL.h>

class IGameEventHandler
{
public:
	virtual void handleGameEvents(const Uint8*) = 0;
};

#endif