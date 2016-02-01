#include "ProgramManager.h"

ProgramManager::ProgramManager(SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	paused = false;

	EventManager::Instance()->registerHandler(this);
}

ProgramManager::~ProgramManager()
{
	EventManager::Instance()->deregisterHandler(this);
}

void ProgramManager::gameLoop()
{
	GameManager* gameManager = new GameManager();
	Uint64 frameTime, lastFrameTime = 0;
	SDL_Event e;

	//Keep the game running until the game manager wants to quit
	while(!gameManager->shouldQuit())
	{
		//Quit early if a quit event is detected
		while( SDL_PollEvent( &e ) != 0 )
 		{
 			if(e.type == SDL_QUIT)
 			{
 				delete gameManager;
 				return;
 			}
 		}

 		EventManager::Instance()->handleKeyboardEvents();
 		EventManager::Instance()->handleGameEvents();

 		if(!paused)
 		{
			gameManager->update(frameTime - lastFrameTime);
			gameManager->render(gRenderer);

		}

		lastFrameTime = frameTime;
		frameTime = SDL_GetPerformanceCounter();
	}

	delete gameManager;
}

void ProgramManager::handleKeyboardEvents(const Uint8* keyStates)
{
	static bool lastPauseState = false;

	bool currentPauseState = keyStates[SDL_SCANCODE_P] | keyStates[SDL_SCANCODE_ESCAPE];

	if(lastPauseState != currentPauseState && currentPauseState)
	{
		paused = !paused;
	}

	lastPauseState = currentPauseState;
}

void ProgramManager::handleGameEvents(const Uint8* events)
{

}

char* ProgramManager::type()
{
	return "ProgramManager";
}