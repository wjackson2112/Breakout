#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
//#include <map>
//#include "Entity.h"
#include "IEventHandler.h"

class EventManager
{
private:
	//Singleton vars
	static bool instanceFlag;
	static EventManager* instance;
	std::vector<IEventHandler*> eventHandlers;

	SDL_Event e;

	EventManager(){};
public:

	static EventManager* Instance();
	void registerHandler(IEventHandler* handler);
	void deregisterHandler(IEventHandler* handler);
	void handleEvents();
};

#endif