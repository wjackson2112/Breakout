#include "MenuManager.h"

MenuManager::MenuManager(AssetFactory* assetFactory)
{
	visible = true;
	this->assetFactory = assetFactory;
	EventManager::Instance()->registerHandler(this);

	this->pushMenu(MAIN_MENU);
}

MenuManager::~MenuManager()
{
	EventManager::Instance()->deregisterHandler(this);
}

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
			newMenu = new MainMenu(this->assetFactory);
			break;
		case PAUSE_MENU:
			newMenu = new PauseMenu(this->assetFactory);
			break;
		case OPTIONS_MENU:
			newMenu = new OptionsMenu(this->assetFactory);
			break;
		case AUDIO_OPTIONS_MENU:
			newMenu = new AudioOptionsMenu(this->assetFactory);
			break;
		case VIDEO_OPTIONS_MENU:
			newMenu = new VideoOptionsMenu(this->assetFactory);
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