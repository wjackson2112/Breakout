#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
//#include <map>
//#include "Entity.h"
#include "IEventHandler.h"

typedef enum GameEvent
{
	BLOCK_DISAPPEARED = 0,
	BALL_LOST,
	BALLS_DEPLETED,
	NUM_OF_EVENTS
} GameEvent;

class EventManager
{
private:
	//Singleton vars
	static bool instanceFlag;
	static EventManager* instance;
	std::vector<IEventHandler*> eventHandlers;

	Uint8 gameEvents[NUM_OF_EVENTS];

	SDL_Event e;

	EventManager(){};
	void clearGameEvents();
public:

	static EventManager* Instance();
	void registerHandler(IEventHandler* handler);
	void deregisterHandler(IEventHandler* handler);
	void handleKeyboardEvents();
	void reportGameEvent(GameEvent event);
	void handleGameEvents();
};

#endif