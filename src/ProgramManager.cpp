#include "ProgramManager.h"

ProgramManager::ProgramManager(SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	textureFactory = new TextureFactory(gRenderer);
	gameManager = new GameManager(this->textureFactory);
	menuManager = new MenuManager();
	machineState = MENU;
	quit = false;

	EventManager::Instance()->registerHandler(this);
}

ProgramManager::~ProgramManager()
{
	EventManager::Instance()->deregisterHandler(this);
}

void ProgramManager::loop()
{

	Uint64 frameTime, lastFrameTime = 0;
	SDL_Event e;

	//Keep the game running until the game manager wants to quit
	while(!this->quit)
	{
		//Quit early if a quit event is detected
		while( SDL_PollEvent( &e ) != 0 )
 		{
 			if(e.type == SDL_QUIT)
 			{
 				delete gameManager;
 				delete menuManager;
 				return;
 			}
 		}

 		//Handle Events
 		EventManager::Instance()->handleMouseEvents();
 		EventManager::Instance()->handleKeyboardEvents();
 		EventManager::Instance()->handleGameEvents();

 		//Update Managers
 		gameManager->update(frameTime - lastFrameTime);
 		menuManager->update(frameTime - lastFrameTime);

 		//Render
		SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(gRenderer);

 		gameManager->render(gRenderer);
 		menuManager->render(gRenderer);

 		SDL_RenderPresent(gRenderer);


		lastFrameTime = frameTime;
		frameTime = SDL_GetPerformanceCounter();
	}

	delete gameManager;
	delete menuManager;
}

void ProgramManager::handleMouseEvents(int mouseState, int x, int y)
{

}

void ProgramManager::handleKeyboardEvents(const Uint8* keyStates)
{
	static bool lastPause = false;
	bool pause = keyStates[SDL_SCANCODE_P];
	if(lastPause != pause && pause)
	{
		switch(machineState)
		{
			case MENU:
				EventManager::Instance()->reportGameEvent(RESUME_GAME);
				break;
			case GAME:
				EventManager::Instance()->reportGameEvent(PAUSE_GAME);
				break;
			default:
				break;
		}
		
	}
	lastPause = pause;

	static bool lastMenuQuit = false;
	bool menuQuit = keyStates[SDL_SCANCODE_ESCAPE];
	if(lastMenuQuit != menuQuit && menuQuit)
	{
		switch(machineState)
		{
			case MENU:
				break;
			case GAME:
				EventManager::Instance()->reportGameEvent(QUIT_GAME);
				break;
			default:
				break;
		}
		
	}
	lastMenuQuit = menuQuit;
}

void ProgramManager::handleGameEvents(const Uint8* events)
{
	if(events[NEW_GAME])
	{
		machineState = GAME;
	}

	if(events[PAUSE_GAME])
	{
		machineState = MENU;
	}

	if(events[RESUME_GAME])
	{
		machineState = GAME;
	}

	if(events[QUIT_GAME])
	{
		machineState = MENU;
	}

	if(events[QUIT_PROGRAM])
	{
		this->quit = true;
	}
}

char* ProgramManager::type()
{
	return "ProgramManager";
}