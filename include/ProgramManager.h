#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "EventManager.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "IGameEventHandler.h"
#include <iostream>

typedef enum ProgramManagerState
{
	MENU,
	GAME
} ProgramManagerState;

class ProgramManager : public IGameEventHandler, public IKeyboardEventHandler
{
private:
	SDL_Renderer* gRenderer;
	ProgramManagerState machineState;
	GameManager* gameManager;
	MenuManager* menuManager;
	AssetFactory* assetFactory;
	bool quit;
public:
	ProgramManager(SDL_Renderer* gRenderer);
	void loop();
	~ProgramManager();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	char* type();
};

#endif