#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <vector>
#include <cstdlib>
#include <cstring>

#include "IEventHandler.h"
#include "EventManager.h"
#include "UIEntity.h"
#include "Button.h"
#include "Globals.h"
#include "AssetFactory.h"
#include "Menu.h"
#include "StateMachine.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "OptionsMenu.h"

typedef enum
{
	MAIN_MENU,
	PAUSE_MENU,
	OPTIONS_MENU
} MenuType;

class MenuManager : public IEventHandler
{
private:
	//Menu *mainMenu, *pauseMenu, *optionsMenu;
	std::vector<Menu*> menuStack;
	AssetFactory* assetFactory;
	
	// StateMachine<MenuManagerState>* state;
	
	bool visible;
	
	// void setMainMenuButtons();
	// void setPauseMenuButtons();
	// void setOptionsMenuButtons();

	void pushMenu(MenuType menu);
	void popMenu();
	Menu* peekMenu();
	void clearMenuStack();

	// void stateChanged(MenuManagerState prevState, MenuManagerState currState);
public:
	MenuManager(AssetFactory* assetFactory);
	~MenuManager();

	void render(SDL_Renderer*);
	void update(int frameTime);

	char* type();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
};

#endif