#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "EventManager.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "IEventHandler.h"
#include <iostream>

typedef enum ProgramManagerState
{
	MAIN_MENU,
	GAME_RUNNING,
	GAME_PAUSED
} ProgramManagerState;

class ProgramManager : public IEventHandler
{
private:
	SDL_Renderer* gRenderer;
	ProgramManagerState machineState;
public:
	ProgramManager(SDL_Renderer* gRenderer);
	void loop();
	~ProgramManager();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	char* type();
};

#endif