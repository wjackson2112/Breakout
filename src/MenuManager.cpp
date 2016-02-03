#include "MenuManager.h"

MenuManager::MenuManager()
{
	quit = false;
	EventManager::Instance()->registerHandler(this);

	uiEntities.push_back(new Button(""));
}

MenuManager::~MenuManager()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}

	EventManager::Instance()->deregisterHandler(this);
}

bool MenuManager::shouldQuit()
{
	return quit;
}

void MenuManager::render(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderClear(gRenderer);

	for(auto &entity : uiEntities)
	{
		entity->render(gRenderer);
	}

	SDL_RenderPresent(gRenderer);
}

void MenuManager::update(int frameTime)
{
	for(auto &entity : uiEntities)
	{
		entity->update(frameTime);
	}
}

char* MenuManager::type()
{
	return "MenuManager";
}

void MenuManager::handleMouseEvents(int mouseState, int x, int y)
{
	
}

void MenuManager::handleKeyboardEvents(const Uint8* keyStates)
{

}

void MenuManager::handleGameEvents(const Uint8* events)
{

}