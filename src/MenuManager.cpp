#include "MenuManager.h"

MenuManager::MenuManager(AssetFactory* assetFactory)
{
	visible = true;
	this->assetFactory = assetFactory;
	EventManager::Instance()->registerHandler(this);

	this->state = new StateMachine<MenuManagerState>(
						[this](MenuManagerState prevState, MenuManagerState currState) { return this->stateChanged(prevState, currState); },
						MAIN_ST);

	this->setMainMenuButtons();
	mainMenu->enable();
	this->setPauseMenuButtons();
}

MenuManager::~MenuManager()
{
	EventManager::Instance()->deregisterHandler(this);
}

void MenuManager::setMainMenuButtons()
{
	int mainMenuNumRows = 2;
	int mainMenuNumCols = 1;

	this->mainMenu = new Menu(Globals::mainMenuX, 
							  Globals::mainMenuY, 
							  mainMenuNumRows, 
							  Globals::mainMenuRowHeight, 
							  Globals::mainMenuRowPadding, 
							  mainMenuNumCols,
							  Globals::mainMenuColWidth, 
							  Globals::mainMenuColPadding);

	this->mainMenu->add_menu_item(new Button("./png/NewGame.png", this->assetFactory, NEW_GAME), 0, 0);
	this->mainMenu->add_menu_item(new Button("./png/QuitToDesktop.png", this->assetFactory, QUIT_PROGRAM), 1, 0);
}

void MenuManager::setPauseMenuButtons()
{
	int pauseMenuNumRows = 3;
	int pauseMenuNumCols = 1;

	this->pauseMenu = new Menu(Globals::pauseMenuX,
							   Globals::pauseMenuY, 
							   pauseMenuNumRows, 
							   Globals::pauseMenuRowHeight, 
							   Globals::pauseMenuRowPadding, 
							   pauseMenuNumCols, 
							   Globals::pauseMenuColWidth, 
							   Globals::pauseMenuColPadding);
	
	this->pauseMenu->add_menu_item(new Button("./png/ResumeGame.png", this->assetFactory,  RESUME_GAME), 0, 0);
	this->pauseMenu->add_menu_item(new Button("./png/NewGame.png", this->assetFactory, NEW_GAME), 1, 0);
	this->pauseMenu->add_menu_item(new Button("./png/QuitGame.png", this->assetFactory, QUIT_GAME), 2, 0);	
}

void MenuManager::render(SDL_Renderer* gRenderer)
{
	switch(this->state->getState())
	{
		case MAIN_ST:
		{
			SDL_Rect fillRect = {0, 0, Globals::screenWidth, Globals::screenHeight};
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xCC);
			SDL_RenderFillRect(gRenderer, &fillRect);
			this->mainMenu->render(gRenderer);
			break;
		}
		case PAUSE_ST:
		{
			SDL_Rect fillRect = {0, 0, Globals::screenWidth, Globals::screenHeight};
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xCC);
			SDL_RenderFillRect(gRenderer, &fillRect);
			this->pauseMenu->render(gRenderer);
			break;			
		}
	}
}

void MenuManager::update(int frameTime)
{

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
	switch(this->state->getState())
	{
		case NONE_ST:
			if(events[PAUSE_GAME])
			{
				this->state->updateState(PAUSE_ST);
			}
			else if(events[QUIT_GAME])
			{
				this->state->updateState(MAIN_ST);
			}
			break;
		case MAIN_ST:
			if(events[NEW_GAME])
			{
				this->state->updateState(NONE_ST);
			}
			break;
		case PAUSE_ST:
			if(events[NEW_GAME] || events[RESUME_GAME])
			{
				this->state->updateState(NONE_ST);
			} 
			else if(events[QUIT_GAME])
			{
				this->state->updateState(MAIN_ST);
			}
			break;
	}
}

void MenuManager::stateChanged(MenuManagerState prevState, MenuManagerState currState){
	switch(currState)
	{
		case NONE_ST:
			this->mainMenu->disable();
			this->pauseMenu->disable();
			break;
		case MAIN_ST:
			this->mainMenu->enable();
			this->pauseMenu->disable();
			break;
		case PAUSE_ST:
			this->mainMenu->disable();
			this->pauseMenu->enable();
			break; 
	}
}