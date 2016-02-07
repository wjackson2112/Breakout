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

	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "New Game", NEW_GAME, 100, 100));
	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "Quit to Desktop", QUIT_PROGRAM, 100, 175));	
}

void MenuManager::setPauseMenuButtons()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}
	
	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "Resume Game", RESUME_GAME, 100, 100));	
	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "New Game", NEW_GAME, 100, 175));
	uiEntities.push_back(new Button("/usr/local/share/fonts/Anonymous Pro.ttf", "Quit Game", QUIT_GAME, 100, 250));	
}

void MenuManager::render(SDL_Renderer* gRenderer)
{
	if(!visible)
	{
		return;
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