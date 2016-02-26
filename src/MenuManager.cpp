#include "MenuManager.h"

MenuManager::MenuManager()
{
	visible = true;
	EventManager::Instance()->registerHandler(this);

	this->setMainMenuButtons();
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

void MenuManager::setMainMenuButtons()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}

	uiEntities.push_back(new Button("/usr/share/fonts/truetype/inconsolata/Inconsolata.otf", "New Game", NEW_GAME, Globals::screenHeight / 10, Globals::screenHeight / 10));
	uiEntities.push_back(new Button("/usr/share/fonts/truetype/inconsolata/Inconsolata.otf", "Quit to Desktop", QUIT_PROGRAM, Globals::screenHeight / 10, Globals::screenHeight / 10 * 2));	
}

void MenuManager::setPauseMenuButtons()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}
	
	uiEntities.push_back(new Button("/usr/share/fonts/truetype/inconsolata/Inconsolata.otf", "Resume Game", RESUME_GAME, Globals::screenHeight / 10, Globals::screenHeight / 10));	
	uiEntities.push_back(new Button("/usr/share/fonts/truetype/inconsolata/Inconsolata.otf", "New Game", NEW_GAME, Globals::screenHeight / 10, Globals::screenHeight / 10 * 2));
	uiEntities.push_back(new Button("/usr/share/fonts/truetype/inconsolata/Inconsolata.otf", "Quit Game", QUIT_GAME, Globals::screenHeight / 10, Globals::screenHeight / 10 * 3));	
}

void MenuManager::render(SDL_Renderer* gRenderer)
{
	if(!visible)
	{
		return;
	}
	else
	{
		SDL_Rect fillRect = {0, 0, Globals::screenWidth, Globals::screenHeight};
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xCC);
		SDL_RenderFillRect(gRenderer, &fillRect);
	}

	for(auto &entity : uiEntities)
	{
		entity->render(gRenderer);
	}
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
	if(events[NEW_GAME] || events[RESUME_GAME])
	{
		visible = false;
	}

	if(events[PAUSE_GAME])
	{
		visible = true;
		this->setPauseMenuButtons();
	}

	if(events[QUIT_GAME])
	{
		visible = true;
		this->setMainMenuButtons();
	}
}