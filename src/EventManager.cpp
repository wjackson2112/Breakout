#include "EventManager.h"

//Static singleton vars
bool EventManager::instanceFlag = false;
EventManager* EventManager::instance = NULL;

EventManager::EventManager()
{
	this->clearGameEvents();
}

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

void EventManager::printHandlers()
{
	std::cout << "Registered Handlers: |";
	for(auto &handler : eventHandlers)
	{
		std::cout << handler->type() << "|";
	}
	std::cout << std::endl;
}

void EventManager::registerMouseHandler(IMouseEventHandler* handler)
{
	this->mouseEventHandlers.push_back(handler);
}

void EventManager::deregisterMouseHander(IMouseEventHandler* handler)
{
	for(std::vector<IMouseEventHandler*>::iterator it=this->mouseEventHandlers.begin(); it!=this->mouseEventHandlers.end();)
	{
		if(*it == handler)
		{
			it = this->mouseEventHandlers.erase(it);
		}
		else
		{
			++it;
		}
	}	
}

void EventManager::handleMouseEvents()
{
	static int prevX, prevY, prevMouseState;

	int x, y, mouseState;

	SDL_PumpEvents();
	mouseState = SDL_GetMouseState(&x, &y);

	for(int i = SDL_BUTTON_LEFT; i <= SDL_BUTTON_X2; i++)
	{
		if(mouseState & SDL_BUTTON(i) && !(prevMouseState & SDL_BUTTON(i)))
		{
			for(auto &handler : mouseEventHandlers)
			{
				handler->handleMousePress(i, x, y);
			}
		} 
		else if(!(mouseState & SDL_BUTTON(i)) && prevMouseState & SDL_BUTTON(i))
		{
			for(auto &handler : mouseEventHandlers)
			{
				handler->handleMouseRelease(i, x, y);
			}
		}
		else if(mouseState & SDL_BUTTON(i) && prevMouseState & SDL_BUTTON(i))
		{
			for(auto &handler : mouseEventHandlers)
			{
				handler->handleMouseDrag(i, prevX, prevY, x, y);
			}
		}
	}

	prevX = x;
	prevY = y;
	prevMouseState = mouseState;
}

void EventManager::handleKeyboardEvents()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	for(auto &handler : eventHandlers)
	{
		handler->handleKeyboardEvents(keyStates);
	}
}

void EventManager::reportGameEvent(GameEvent event)
{
	this->gameEvents[event] += 1;
}

void EventManager::handleGameEvents()
{
	for(auto &handler : eventHandlers)
	{
		handler->handleGameEvents(gameEvents);
	}
	this->clearGameEvents();
}

void EventManager::clearGameEvents()
{
	for(int i = 0; i < NUM_OF_EVENTS; i++)
	{
		this->gameEvents[i] = 0;
	}
}