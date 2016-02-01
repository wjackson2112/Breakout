#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "EventManager.h"
#include "GameManager.h"
#include "IEventHandler.h"
#include <iostream>

class ProgramManager : public IEventHandler
{
private:
	SDL_Renderer* gRenderer;
	bool paused;
public:
	ProgramManager(SDL_Renderer* gRenderer);
	void gameLoop();
	~ProgramManager();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
};

#endif