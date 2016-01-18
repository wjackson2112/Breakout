#include "EventManager.h"

//Static singleton vars
bool EventManager::instanceFlag = false;
EventManager* EventManager::instance = NULL;

EventManager* EventManager::Instance(){

	if(!instanceFlag)
	{
		instance = new EventManager();
		instanceFlag = true;
	}

	return instance;
}

void EventManager::registerHandler(IEventHandler* handler)
{
	this->eventHandlers.push_back(handler);
}

void EventManager::deregisterHandler(IEventHandler* handler)
{
	for(std::vector<IEventHandler*>::iterator it=this->eventHandlers.begin(); it!=this->eventHandlers.end();)
	{
		if(*it == handler)
		{
			it = this->eventHandlers.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EventManager::handleKeyboardEvents()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	for(auto &handler : eventHandlers)
	{
		handler->handleKeyboardEvents(keyStates);
	}
}

void EventManager::handleGameEvents(int event)
{
	for(auto &handler : eventHandlers)
	{
		handler->handleGameEvents(event);
	}
}