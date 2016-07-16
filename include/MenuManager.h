#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <vector>
#include <cstdlib>
#include <cstring>

#include "IGameEventHandler.h"
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
#include "AudioOptionsMenu.h"
#include "VideoOptionsMenu.h"

typedef enum
{
	MAIN_MENU,
	PAUSE_MENU,
	OPTIONS_MENU,
	VIDEO_OPTIONS_MENU,
	AUDIO_OPTIONS_MENU
} MenuType;

class MenuManager : public IGameEventHandler, public IMouseEventHandler
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

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);

	void handleMousePress(int mouseButton, int x, int y);
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY);
	void handleMouseRelease(int mouseButton, int x, int y);
};

#endif