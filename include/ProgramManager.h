#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "EventManager.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "IEventHandler.h"
#include <iostream>

typedef enum ProgramManagerState
{
	MENU,
	GAME
} ProgramManagerState;

class ProgramManager : public IEventHandler
{
private:
	SDL_Renderer* gRenderer;
	ProgramManagerState machineState;
	GameManager* gameManager;
	MenuManager* menuManager;
	bool quit;
public:
	ProgramManager(SDL_Renderer* gRenderer);
	void loop();
	~ProgramManager();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	char* type();
};

#endif