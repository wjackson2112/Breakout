#ifndef IEVENT_HANDLER_H
#define IEVENT_HANDLER_H

#include <SDL2/SDL.h>

class IEventHandler
{
public:
	virtual void handleKeyboardEvents(const Uint8*) = 0;
	virtual void handleGameEvents(const Uint8*) = 0;
	virtual char* type() = 0;
};

#endif