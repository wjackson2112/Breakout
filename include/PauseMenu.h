#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Menu.h"
#include "AssetFactory.h"
#include "Options.h"

class PauseMenu : public Menu
{
public:
	PauseMenu(AssetFactory* assetFactory, Options* options);
};

#endif