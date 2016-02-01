#include "ProgramManager.h"

ProgramManager::ProgramManager(SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	machineState = MAIN_MENU;

	EventManager::Instance()->registerHandler(this);
}

ProgramManager::~ProgramManager()
{
	EventManager::Instance()->deregisterHandler(this);
}

void ProgramManager::loop()
{
	GameManager* gameManager = new GameManager();
	MenuManager* menuManager = new MenuManager();
	Uint64 frameTime, lastFrameTime = 0;
	SDL_Event e;

	//Keep the game running until the game manager wants to quit
	while(!gameManager->shouldQuit() && !menuManager->shouldQuit())
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

 		EventManager::Instance()->handleKeyboardEvents();
 		EventManager::Instance()->handleGameEvents();

 		switch(machineState){
 			case MAIN_MENU:
 				menuManager->update(frameTime - lastFrameTime);
 				menuManager->render(gRenderer);
 				break;
 			case GAME_RUNNING:
 			 	gameManager->update(frameTime - lastFrameTime);
				gameManager->render(gRenderer);
 				break;
 			case GAME_PAUSED:
 				gameManager->render(gRenderer);
 				break;
 			default:
 				std::cout << "ERROR: Invalid ProgramManager State" << std::endl;
				delete gameManager;
				delete menuManager;
				return;
 		}

		lastFrameTime = frameTime;
		frameTime = SDL_GetPerformanceCounter();
	}

	delete gameManager;
	delete menuManager;
}

void ProgramManager::handleKeyboardEvents(const Uint8* keyStates)
{
	static bool lastPause = false;
	bool pause = keyStates[SDL_SCANCODE_P];
	if(lastPause != pause && pause)
	{
		switch(machineState)
		{
			case MAIN_MENU:
				break;
			case GAME_RUNNING:
				machineState = GAME_PAUSED;
				break;
			case GAME_PAUSED:
				machineState = GAME_RUNNING;
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
			case MAIN_MENU:
				break;
			case GAME_RUNNING:
				machineState = MAIN_MENU;
				break;
			case GAME_PAUSED:
				machineState = MAIN_MENU;
				break;
			default:
				break;
		}
	}
	lastMenuQuit = menuQuit;

	static bool lastStart = false;
	bool start = keyStates[SDL_SCANCODE_RETURN];
	if(lastStart != start && start)
	{
		switch(machineState)
		{
			case MAIN_MENU:
				machineState = GAME_RUNNING;
				EventManager::Instance()->reportGameEvent(NEW_GAME);
				break;
			case GAME_RUNNING:
				break;
			case GAME_PAUSED:
				break;
			default:
				break;
		}
	}
	lastStart = start;
}

void ProgramManager::handleGameEvents(const Uint8* events)
{

}

char* ProgramManager::type()
{
	return "ProgramManager";
}