#include "MenuManager.h"

MenuManager::MenuManager(AssetFactory* assetFactory, Options* options)
{
	visible = true;
	this->assetFactory = assetFactory;
	this->options = options;

	this->pushMenu(MAIN_MENU);

	EventManager::Instance()->registerGameEventHandler(this);
	EventManager::Instance()->registerMouseEventHandler(this);
}

MenuManager::~MenuManager()
{
	EventManager::Instance()->deregisterGameEventHandler(this);
	EventManager::Instance()->deregisterMouseEventHandler(this);	
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
	Menu* activeMenu = this->peekMenu();

	if(activeMenu)
	{
		activeMenu->update(frameTime);
	}
}

char* MenuManager::type()
{
	return "MenuManager";
}

void MenuManager::handleMousePress(int mouseButton, int x, int y)
{
	Menu* activeMenu = this->peekMenu();

	if(activeMenu)
	{
		activeMenu->handleMousePress(mouseButton, x, y);
	}
}

void MenuManager::handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY)
{
	Menu* activeMenu = this->peekMenu();

	if(activeMenu)
	{
		activeMenu->handleMouseDrag(mouseButton, prevX, prevY, currX, currY);
	}
}

void MenuManager::handleMouseRelease(int mouseButton, int x, int y)
{
	Menu* activeMenu = this->peekMenu();

	if(activeMenu)
	{
		activeMenu->handleMouseRelease(mouseButton, x, y);
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
		options->write();
		popMenu();
	}
}

void MenuManager::pushMenu(MenuType menuType)
{	
	Menu* newMenu;

	switch(menuType)
	{
		case MAIN_MENU:
			newMenu = new MainMenu(this->assetFactory, this->options);
			break;
		case PAUSE_MENU:
			newMenu = new PauseMenu(this->assetFactory, this->options);
			break;
		case OPTIONS_MENU:
			newMenu = new OptionsMenu(this->assetFactory, this->options);
			break;
		case AUDIO_OPTIONS_MENU:
			newMenu = new AudioOptionsMenu(this->assetFactory, this->options);
			break;
		case VIDEO_OPTIONS_MENU:
			newMenu = new VideoOptionsMenu(this->assetFactory, this->options);
			break;
	}

	if(this->menuStack.size() >= 1)
	{
		newMenu->add_floating_menu_item(new Button("./png/Back.png", assetFactory, options, BACK), 25, 25);
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