#include "PauseMenuManager.h"

PauseMenuManager::PauseMenuManager()
{
	quit = false;
	EventManager::Instance()->registerHandler(this);

	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "New Game", NEW_GAME, 100, 100));
	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "Resume Game", RESUME_GAME, 100, 175));
	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "Quit Game", QUIT_GAME, 100, 250));
}

PauseMenuManager::~PauseMenuManager()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}

	EventManager::Instance()->deregisterHandler(this);
}

bool PauseMenuManager::shouldQuit()
{
	return quit;
}

void PauseMenuManager::render(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderClear(gRenderer);

	for(auto &entity : uiEntities)
	{
		entity->render(gRenderer);
	}

	SDL_RenderPresent(gRenderer);
}

void PauseMenuManager::update(int frameTime)
{
	for(auto &entity : uiEntities)
	{
		entity->update(frameTime);
	}
}

char* PauseMenuManager::type()
{
	return "MenuManager";
}

void PauseMenuManager::handleMouseEvents(int mouseState, int x, int y)
{
	
}

void PauseMenuManager::handleKeyboardEvents(const Uint8* keyStates)
{

}

void PauseMenuManager::handleGameEvents(const Uint8* events)
{

}