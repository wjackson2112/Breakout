#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"
#include "AssetFactory.h"
#include "Options.h"

class MainMenu : public Menu
{
public:

	MainMenu(AssetFactory* assetFactory, Options* options);
};

#endif