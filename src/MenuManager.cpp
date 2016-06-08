#include "MenuManager.h"

MenuManager::MenuManager(AssetFactory* assetFactory)
{
	visible = true;
	this->assetFactory = assetFactory;
	EventManager::Instance()->registerHandler(this);

	// this->state = new StateMachine<MenuManagerState>(
	// 					[this](MenuManagerState prevState, MenuManagerState currState) { return this->stateChanged(prevState, currState); },
	// 					MAIN_ST);

	// this->setMainMenuButtons();
	// this->setPauseMenuButtons();
	// this->setOptionsMenuButtons();

	this->pushMenu(MAIN_MENU);
}

MenuManager::~MenuManager()
{
	EventManager::Instance()->deregisterHandler(this);
}

// void MenuManager::setMainMenuButtons()
// {
// 	int rows = 3;
// 	int cols = 1;

// 	this->mainMenu = new Menu(Globals::mainMenuX, 
// 							  Globals::mainMenuY, 
// 							  rows, 
// 							  Globals::mainMenuRowHeight, 
// 							  Globals::mainMenuRowPadding, 
// 							  cols,
// 							  Globals::mainMenuColWidth, 
// 							  Globals::mainMenuColPadding);

// 	this->mainMenu->add_menu_item(new Button("./png/NewGame.png", this->assetFactory, NEW_GAME), 0, 0);
// 	this->mainMenu->add_menu_item(new Button("./png/Options.png", this->assetFactory, OPTIONS), 1, 0);
// 	this->mainMenu->add_menu_item(new Button("./png/QuitToDesktop.png", this->assetFactory, QUIT_PROGRAM), 2, 0);
// }

// void MenuManager::setPauseMenuButtons()
// {
// 	int rows = 4;
// 	int cols = 1;

// 	this->pauseMenu = new Menu(Globals::pauseMenuX,
// 							   Globals::pauseMenuY, 
// 							   rows, 
// 							   Globals::pauseMenuRowHeight, 
// 							   Globals::pauseMenuRowPadding, 
// 							   cols, 
// 							   Globals::pauseMenuColWidth, 
// 							   Globals::pauseMenuColPadding);
	
// 	this->pauseMenu->add_menu_item(new Button("./png/ResumeGame.png", this->assetFactory,  RESUME_GAME), 0, 0);
// 	this->pauseMenu->add_menu_item(new Button("./png/NewGame.png", this->assetFactory, NEW_GAME), 1, 0);
// 	this->pauseMenu->add_menu_item(new Button("./png/Options.png", this->assetFactory, OPTIONS), 2, 0);
// 	this->pauseMenu->add_menu_item(new Button("./png/QuitGame.png", this->assetFactory, QUIT_GAME), 3, 0);	
// }

// void MenuManager::setOptionsMenuButtons()
// {
// 	int rows = 1;
// 	int cols = 2;

// 	this->optionsMenu = new Menu(Globals::mainMenuX, 
// 							  Globals::mainMenuY, 
// 							  rows, 
// 							  Globals::mainMenuRowHeight, 
// 							  Globals::mainMenuRowPadding, 
// 							  cols,
// 							  Globals::mainMenuColWidth, 
// 							  Globals::mainMenuColPadding);

// 	//TODO: Make this a label and dropdown (slider?)
// 	this->optionsMenu->add_menu_item(new Button("./png/Options.png", this->assetFactory, BACK), 0, 0);
// 	this->optionsMenu->add_menu_item(new Button("./png/Options.png", this->assetFactory, BACK), 1, 0);
// }

void MenuManager::render(SDL_Renderer* gRenderer)
{
	Menu* activeMenu = this->peekMenu();

	if(activeMenu)
	{
		SDL_Rect fillRect = {0, 0, Globals::screenWidth, Globals::screenHeight};
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xCC);
		SDL_RenderFillRect(gRenderer, &fillRect);
		activeMenu->render(gRenderer);		
	}

	// switch(this->state->getState())
	// {
	// 	case MAIN_ST:
	// 	{
	// 		SDL_Rect fillRect = {0, 0, Globals::screenWidth, Globals::screenHeight};
	// 		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xCC);
	// 		SDL_RenderFillRect(gRenderer, &fillRect);
	// 		this->mainMenu->render(gRenderer);
	// 		break;
	// 	}
	// 	case PAUSE_ST:
	// 	{
	// 		SDL_Rect fillRect = {0, 0, Globals::screenWidth, Globals::screenHeight};
	// 		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xCC);
	// 		SDL_RenderFillRect(gRenderer, &fillRect);
	// 		this->pauseMenu->render(gRenderer);
	// 		break;			
	// 	}
	// }

	// MenuManagerState activeMenu = this->peekMenu();

	// switch(activeMenu)
	// {
	// 	case NONE_ST:
	// 		break;
	// 	case MAIN_ST:
	// 		mainMenu->render(gRenderer);
	// 		break;
	// 	case PAUSE_ST:
	// 		pauseMenu->render(gRenderer);
	// 		break;
	// 	case OPTIONS_ST:
	// 		optionsMenu->render(gRenderer);
	// 		break;
	// }

	// if(activeMenu != NULL){
	// 	activeMenu->render(gRenderer);
	// }
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
	static bool lastState = false;
	Menu* activeMenu = this->peekMenu();

	if((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
		lastState == false)
	{
		lastState = true;
	}
	else if(!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && 
			lastState == true)
	{
		if(activeMenu)
		{
			GameEvent event = activeMenu->handleClick(x, y);
			if(event != NO_EVENT)
			{
				EventManager::Instance()->reportGameEvent(event);
			}
		}
		lastState = false;
	}
}

void MenuManager::handleKeyboardEvents(const Uint8* keyStates)
{

}

void MenuManager::handleGameEvents(const Uint8* events)
{
	if(events[NEW_GAME] || events[RESUME_GAME])
	{
		this->clearMenuStack();	
	}

	if(events[PAUSE_GAME])
	{
		this->pushMenu(PAUSE_MENU);
	}

	if(events[QUIT_GAME])
	{
		this->clearMenuStack();
		this->pushMenu(MAIN_MENU);
	}

	if(events[OPTIONS])
	{
		this->pushMenu(OPTIONS_MENU);
	}

	if(events[VIDEO_OPTIONS])
	{
		this->pushMenu(VIDEO_OPTIONS_MENU);
	}

	if(events[AUDIO_OPTIONS])
	{
		this->pushMenu(AUDIO_OPTIONS_MENU);
	}

	if(events[BACK])
	{
		this->popMenu();
	}
}

void MenuManager::pushMenu(MenuType menuType)
{	
	Menu* newMenu;

	switch(menuType)
	{
		case MAIN_MENU:
			newMenu = new MainMenu(Globals::mainMenuX, 
								   Globals::mainMenuY, 
								   Globals::mainMenuRowHeight, 
								   Globals::mainMenuRowPadding,
								   Globals::mainMenuColWidth,
								   Globals::mainMenuColPadding,
								   this->assetFactory);
			break;
		case PAUSE_MENU:
			newMenu = new PauseMenu(Globals::pauseMenuX, 
						   		    Globals::pauseMenuY, 
						   		    Globals::pauseMenuRowHeight, 
						   		    Globals::pauseMenuRowPadding,
						   		    Globals::pauseMenuColWidth,
						   		    Globals::pauseMenuColPadding,
						   		    this->assetFactory);
			break;
		case OPTIONS_MENU:
			newMenu = new OptionsMenu(Globals::mainMenuX, 
						   		      Globals::mainMenuY, 
						   		      Globals::mainMenuRowHeight, 
						   		      Globals::mainMenuRowPadding,
						   		      Globals::mainMenuColWidth,
						   		      Globals::mainMenuColPadding,
						   		      this->assetFactory);
			break;
		case AUDIO_OPTIONS_MENU:
			newMenu = new AudioOptionsMenu(Globals::mainMenuX, 
						   		      	   Globals::mainMenuY, 
						   		           Globals::mainMenuRowHeight, 
						   		           Globals::mainMenuRowPadding,
						   		           Globals::mainMenuColWidth,
						   		           Globals::mainMenuColPadding,
						   		           this->assetFactory);
			break;
		case VIDEO_OPTIONS_MENU:
			newMenu = new VideoOptionsMenu(Globals::mainMenuX, 
						   		           Globals::mainMenuY, 
						   		           Globals::mainMenuRowHeight, 
						   		           Globals::mainMenuRowPadding,
						   		           Globals::mainMenuColWidth,
						   		           Globals::mainMenuColPadding,
						   		           this->assetFactory);
			break;
	}

	if(this->menuStack.size() >= 1)
	{
		newMenu->add_floating_menu_item(new Button("./png/Back.png", assetFactory, BACK), 25, 25);
	}

	this->menuStack.push_back(newMenu);
}

void MenuManager::popMenu()
{
	this->menuStack.pop_back();
}

Menu* MenuManager::peekMenu()
{
	if(this->menuStack.size() != 0)
	{
		return this->menuStack.back();
	}
	return NULL;
}

void MenuManager::clearMenuStack()
{
	this->menuStack.clear();
}

// void MenuManager::stateChanged(MenuManagerState prevState, MenuManagerState currState){
// 	// switch(currState)
// 	// {
// 	// 	case NONE_ST:
// 	// 		// this->activeMenu = NULL;
// 	// 		break;
// 	// 	case MAIN_ST:
// 	// 		// this->activeMenu = mainMenu;
// 	// 		break;
// 	// 	case PAUSE_ST:
// 	// 		// this->pauseMenu = pauseMenu;
// 	// 		break; 
// 	// 	case OPTIONS_ST:
// 	// 		// this->optionsMenu = optionsMenu;
// 	// 		break;
// 	// }
// }