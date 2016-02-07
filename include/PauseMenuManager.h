#ifndef PAUSE_MENU_MANAGER_H
#define PAUSE_MENU_MANAGER_H

#include <vector>
#include <cstdlib>
#include <cstring>

#include "MenuManager.h"
#include "EventManager.h"
#include "UIEntity.h"
#include "Button.h"
#include "Globals.h"

class PauseMenuManager : public MenuManager
{
private:
	std::vector<UIEntity*> uiEntities;
	bool quit;

public:
	PauseMenuManager();
	~PauseMenuManager();

	bool shouldQuit();
	void render(SDL_Renderer*);
	void update(int frameTime);

	char* type();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
};

#endif