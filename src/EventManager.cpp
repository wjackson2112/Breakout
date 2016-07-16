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

template<typename T>
void registerEventHandler(std::vector<T*> &eventHandlers, T* handler)
{
	eventHandlers.push_back(handler);
}

template<typename T>
void deregisterEventHandler(std::vector<T*> &eventHandlers, T* handler)
{
	for(typename std::vector<T*>::iterator it=eventHandlers.begin(); it!=eventHandlers.end();)
	{
		if(*it == handler)
		{
			it = eventHandlers.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void EventManager::registerGameEventHandler(IGameEventHandler* handler)
{
	registerEventHandler(this->gameEventHandlers, handler);
}

void EventManager::deregisterGameEventHandler(IGameEventHandler* handler)
{
	deregisterEventHandler(this->gameEventHandlers, handler);
}

void EventManager::registerMouseEventHandler(IMouseEventHandler* handler)
{
	registerEventHandler(this->mouseEventHandlers, handler);
}

void EventManager::deregisterMouseEventHandler(IMouseEventHandler* handler)
{
	deregisterEventHandler(this->mouseEventHandlers, handler);	
}

void EventManager::registerKeyboardEventHandler(IKeyboardEventHandler* handler)
{
	registerEventHandler(this->keyboardEventHandlers, handler);
}

void EventManager::deregisterKeyboardEventHandler(IKeyboardEventHandler* handler)
{
	deregisterEventHandler(this->keyboardEventHandlers, handler);	
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
	for(auto &handler : keyboardEventHandlers)
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
	for(auto &handler : gameEventHandlers)
	{
		if(handler == NULL)
		{
			std::cout << "PROBLEM" << std::endl;
		}
		handler->handleGameEvents(this->gameEvents);
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

// void EventManager::printHandlers()
// {
// 	std::cout << "Registered Handlers: |";
// 	for(auto &handler : eventHandlers)
// 	{
// 		std::cout << handler->type() << "|";
// 	}
// 	std::cout << std::endl;
// }