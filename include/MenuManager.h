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

typedef enum
{
	NONE_ST,
	MAIN_ST,
	PAUSE_ST
} MenuManagerState;

class MenuManager : public IEventHandler
{
private:
	Menu *mainMenu, *pauseMenu;
	AssetFactory* assetFactory;
	StateMachine<MenuManagerState>* state;
	bool visible;
	void setMainMenuButtons();
	void setPauseMenuButtons();
	void stateChanged(MenuManagerState prevState, MenuManagerState currState);
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