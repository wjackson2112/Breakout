#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
//#include <map>
//#include "Entity.h"
#include "IGameEventHandler.h"
#include "IMouseEventHandler.h"
#include "IKeyboardEventHandler.h"

typedef enum GameEvent
{
	NO_EVENT = 0,
	BLOCK_DISAPPEARED,
	BALL_ADDED,
	BALL_LOST,
	BALLS_DEPLETED,
	NEW_GAME,
	PAUSE_GAME,
	RESUME_GAME,
	OPTIONS,
	VIDEO_OPTIONS,
	AUDIO_OPTIONS,
	BACK,
	CREDITS,
	QUIT_GAME,
	QUIT_PROGRAM,
	NUM_OF_EVENTS
} GameEvent;

static char* GameEventStr[NUM_OF_EVENTS] =
{
	"BLOCK_DISAPPEARED",
	"BALL_ADDED",
	"BALL_LOST",
	"BALLS_DEPLETED",
	"NEW_GAME",
	"PAUSE_GAME",
	"RESUME_GAME",
	"OPTIONS",
	"VIDEO_OPTIONS",
	"AUDIO_OPTIONS",
	"BACK",
	"CREDITS",
	"QUIT_GAME",
	"QUIT_PROGRAM"
};

class EventManager
{
private:
	//Singleton vars
	static bool instanceFlag;
	static EventManager* instance;
	std::vector<IGameEventHandler*> gameEventHandlers;
	std::vector<IMouseEventHandler*> mouseEventHandlers;
	std::vector<IKeyboardEventHandler*> keyboardEventHandlers;

	Uint8 gameEvents[NUM_OF_EVENTS] = {{0}};

	SDL_Event e;

	EventManager();
	void clearGameEvents();

public:
	static EventManager* Instance();

	void registerGameEventHandler(IGameEventHandler* handler);
	void deregisterGameEventHandler(IGameEventHandler* handler);

	void registerMouseEventHandler(IMouseEventHandler* handler);
	void deregisterMouseEventHandler(IMouseEventHandler* handler);

	void registerKeyboardEventHandler(IKeyboardEventHandler* handler);
	void deregisterKeyboardEventHandler(IKeyboardEventHandler* handler);

	//void printHandlers();
	void handleKeyboardEvents();
	void reportSDLEvent(SDL_Event e);
	void reportGameEvent(GameEvent event);
	void handleGameEvents();


	void handleMouseEvents();
};

#endif